#include<fstream>
#include"StarMatrix.h"
#include"Config.h"
#include"GameLayer.h"
//#include"CSVParser.h"
#include"MyUserData.h"
#include"ChallengeGameLayer.h"
#include"MusicManagement.h"
//using namespace CSVParser;
GameLayer* StarMatrix::gameLayer = nullptr;
ChallengeGameLayer* StarMatrix::challengeGameLayer = nullptr;
void StarMatrix::initData(){
	_rowNum = 10;
	_colNum = 10;
	_offsetY = 93;
	_moveSpeed = 500.0f;
	_selectBG = nullptr;
	_winSize = Director::getInstance()->getVisibleSize();
	_remainingCount = 0;
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(StarMatrix::removeSelectBox), REMOVE_SELECT_BOX, NULL);
}

StarMatrix::~StarMatrix(){
	NotificationCenter::getInstance()->removeAllObservers(this);
}
Vec2 StarMatrix::getPositionByIndex(int i, int j){
	Vec2 location;
	location.x = Star::STAR_WIDTH*j + Star::STAR_WIDTH / 2;
	location.y = Star::STAR_HEIGHT*i + Star::STAR_HEIGHT / 2 + _offsetY;
	return location;
}

void StarMatrix::starTouchJudge(Vec2 touch, Prop* prop){

	Star* star = getStarByTouch(touch);
	if (prop==nullptr){
		if (star != nullptr){
			//log("you touch star");
			//��������Ѿ���ѡ����ˣ���ô��ֱ��ɾ���������û����ѡ������ɾ��������
			if (star->getIsSelected() == true){
				//��������
				deleteSelectedStar();
				//ÿ������֮�󣬶�Ҫ�жϣ�����û�п��Լ��������ġ�
				
			}
			else{
				getSelectedStar(star);
			}
		}
	}///������ڵ��ߵ�ʵ�ֻ���������ģ�ը����Ҫ����͸�������Ҫ������˾�������ǣ����ǽ�����
	//��ɫȴ��Ҫ�������ǵ�λ��
	else {//�����ڿյĻ����Ϳ�����ÿһ���������ʵ�������ˡ�
		switch (prop->getCateGory())
		{
		case Prop::PROP_BOOM:
			if (star!=nullptr){
				MusicManagement::getInstance()->playPropBoom();
				starPropBoom(star);
			}
			break;
		case Prop::PROP_PAINT:
			MusicManagement::getInstance()->playPropPaint();
			starPropPaint();
			break;
		case Prop::PROP_STICK:
			if (star!=nullptr){
				MusicManagement::getInstance()->playPropStick();
				starPropStick(star);
			}
			break;
		case Prop::PROP_TRANS:
			MusicManagement::getInstance()->playPropTrans();
			starPropTrans();
			break;
		default:
			break;
		}
	}
}
void StarMatrix::freshenStarMatrix(){
	for (auto const temp : _selectStarArray){
		temp->stopAllActions();
		temp->setScale(1.0f);
		temp->setIsSelected(false);
	}
	_selectStarArray.clear();
}
void StarMatrix::starPropBoom(Star* star){
	freshenStarMatrix();
	//ɾ��һ���Ź���
	int indexi = star->getRowIndex();
	int indexj = star->getColIndex();

	//��ʼɾ���Ĳ���
	for (int i = -1; i <= 1;++i){
		for (int j = -1; j <= 1;++j){
			int tempi = indexi + i;
			int tempj = indexj + j;
			//û��Խ��//����ָ��Ϊ�ձ�ʾ���Լ���ɾ���Ķ���
			if (tempi>=0&&tempi<_rowNum&&tempj>=0&&tempj<_colNum&&_starArray[tempi][tempj]!=nullptr){
				_selectStarArray.push_back(_starArray[tempi][tempj]);
			}
		}
	}
	//����ɾ�������
	deleteSelectedStar();
	NotificationCenter::getInstance()->postNotification(PROP_COMPLATE);
}
void StarMatrix::produceSelectBox(Star* star){
	if (_selectBG!=nullptr){
		_selectBG->removeFromParent();
		_selectBG = nullptr;
	}
	int indexi = star->getRowIndex();
	int indexj = star->getColIndex();

	//��ʼ�����Ǹ�����
	//����
	_selectBG = Sprite::create("texture/paint_bg.png");
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* unuse_event){
		if (_selectBG->getBoundingBox().containsPoint(touch->getLocation())){
			log("hello BG");
			return true;
		}
		else{
			return false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,_selectBG);
	//selectBG->setScale(0.5f);
	Vec2 location;
	float starWidth = indexj*Star::STAR_WIDTH;
	float bgWidth = _selectBG->getContentSize().width / 2;
	if ((starWidth<bgWidth)){
		location.x = bgWidth;
	}
	else if (starWidth>_winSize.width - bgWidth){
		location.x = _winSize.width - bgWidth;
	}
	else{
		location.x = indexj*Star::STAR_WIDTH;
	}
	location.y = star->getPositionY() + Star::STAR_HEIGHT * 2;
	_selectBG->setPosition(location);
	this->addChild(_selectBG);
	//�±�
	auto selectPoint = Sprite::create("texture/paint_arrow.png");
	selectPoint->setAnchorPoint(Vec2(0.5, 1));
	selectPoint->setPosition(Vec2(star->getPositionX(), _selectBG->getPositionY() - _selectBG->getContentSize().height / 3));
	//selectPoint->setScale(0.5f);
	Vec2 pointLocation = _selectBG->convertToNodeSpace(selectPoint->getPosition());
	selectPoint->setPosition(pointLocation);
	_selectBG->addChild(selectPoint);
	//ѡ�������
	Vector<MenuItem*> menuitemV;

	for (int i = 1; i <= Star::STAR_CATEGORY_NUM; ++i){
		if (i != star->getCateGory()){
			Star::STAR_CATEGORY tempStarCate = (Star::STAR_CATEGORY)i;
			std::string filename = star->getImageName(tempStarCate);
			auto spr_1 = Sprite::createWithSpriteFrameName(filename);
			auto spr_2 = Sprite::createWithSpriteFrameName(filename);
			auto * tempStar = MenuItemSprite::create(spr_1, spr_2, [i,filename,star,this](Ref* sender){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
				//auto image = TextureCache::getInstance()->add
				star->setSpriteFrame(frame);
				//star->setTexture(frame->getTexture());
				star->setCateGory((Star::STAR_CATEGORY)i);
				this->removeSelectBox((Ref*)"");
				NotificationCenter::getInstance()->postNotification(PROP_COMPLATE);
			});
			//tempStar->setTag(i);
			menuitemV.pushBack(tempStar);
			//tempStar->setPosition(Vec2(i*Star::STAR_WIDTH*1.5f, 20));
		}
	}
	//����
	auto returnitem = MenuItemImage::create("texture/paint_back.png", "texture/paint_back.png", [this](Ref* sender){
		//this->removeFromParent();
		_selectBG->removeFromParent();
		_selectBG = nullptr;
		NotificationCenter::getInstance()->postNotification(PROP_COMPLATE);
	});
	menuitemV.pushBack(returnitem);

	auto menu = Menu::createWithArray(menuitemV);
	menu->alignItemsHorizontallyWithPadding(10.0f);
	menu->setPosition(Vec2(_selectBG->getContentSize().width / 2, _selectBG->getContentSize().height / 2));
	_selectBG->addChild(menu);
}
void StarMatrix::starPropStick(Star* star){
	//�����Ǹ�ѡ��Ľ��档��ʹ�á�
	freshenStarMatrix();
	//���ǰ��µ�λ�á�
	produceSelectBox(star);

}

void StarMatrix::starPropPaint(){
	//�����ٵı�����ġ�
	int categoryArr[6] = {0};

	for (int i = 0; i < _rowNum;++i){
		for (int j = 0; j < _colNum;++j){
			if (_starArray[i][j]!=nullptr){
				//ͳ���������������
				++categoryArr[_starArray[i][j]->getCateGory()];
			}
		}
	}
	//�õ����ٵĺ��������ǵ��±�
	int minlocation = 1, maxlocation = 1;
	//int minValue = INT_MAX;
	//int maxValue = categoryArr[maxlocation];
	for (int i = 1; i <=5;++i){
		//���ٵ�
		if (categoryArr[minlocation]<=0){
			//categoryArr[minlocation] = categoryArr[i];
			minlocation = i;
		}
		if (categoryArr[minlocation]>categoryArr[i]&&categoryArr[i]!=0){
			//categoryArr[minlocation] = categoryArr[i];
			minlocation = i;
		}
		//����
		if (categoryArr[maxlocation]<categoryArr[i]){
			//categoryArr[maxlocation] = categoryArr[i];
			maxlocation = i;
		}
	}
	//��õ���������С����ͳ�ơ�
	//log("min  =  %d      max     =   %d",minlocation,maxlocation);
	//log("minValue    =   %d         maxValue       =  %d",categoryArr[minlocation],categoryArr[maxlocation]);
	if (categoryArr[minlocation]>0&&minlocation!=maxlocation){
		//��С�ı�����ġ�
		for (int i = 0; i < _rowNum; ++i){
			for (int j = 0; j < _colNum; ++j){
				if (_starArray[i][j] != nullptr){
					//ͳ���������������
					if (_starArray[i][j]->getCateGory()==minlocation){
						std::string filename = Star::getImageName((Star::STAR_CATEGORY)maxlocation);
						auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
						_starArray[i][j]->setSpriteFrame(frame);
						_starArray[i][j]->setCateGory((Star::STAR_CATEGORY)maxlocation);
					}
					
				}
			}
		}


		//��֪ͨ����ʾ����ִ������ˡ�
		NotificationCenter::getInstance()->postNotification(PROP_COMPLATE,(Ref*)true);
		log("paint true");
	}
	else{
		log("paint false");
		NotificationCenter::getInstance()->postNotification(PROP_COMPLATE, (Ref*)false);
	}
}
Star* StarMatrix::getStarByTouch(Vec2 touch){
	if ((touch.y-_offsetY)<0){
		return nullptr;
	}
	int i = (touch.y - _offsetY) / Star::STAR_HEIGHT;
	int j = (touch.x) / Star::STAR_WIDTH;
	//log("i = %d    j = %d",i,j);
	if (i >= 0 && i<_rowNum&&j >= 0 && j<_colNum){
		return _starArray[i][j];
	}
	else{
		return nullptr;
	}
}
void StarMatrix::starPropTrans(){
	//����һ�����ǵ�λ�á�
	int starSum = 0;
	for (int i = 0; i < _rowNum; ++i){
		for (int j = 0; j < _colNum; ++j){
			if (_starArray[i][j] != nullptr){
				starSum = starSum + 1;
			}
		}
	}
	int count = 0, sumCount = starSum/2;
	while (count<sumCount){
		int oneI;
		int oneJ;
		while (true){
			oneI = random(0, _rowNum - 1);
			oneJ = random(0, _colNum - 1);
			if (_starArray[oneI][oneJ]!=nullptr){
				break;
			}
		}
		int twoI, twoJ;
		while (true){
			twoI = random(0, _rowNum - 1);
			twoJ = random(0, _colNum - 1);
			if (_starArray[twoI][twoJ] != nullptr&&_starArray[oneI][oneJ]!=_starArray[twoI][twoJ]){
				break;
			}
		}
		//swap();
		//���ͱ仯һ��
		Star::STAR_CATEGORY tempcate = _starArray[oneI][oneJ]->getCateGory();
		_starArray[oneI][oneJ]->setCateGory(_starArray[twoI][twoJ]->getCateGory());
		_starArray[twoI][twoJ]->setCateGory(tempcate);

		auto tempFrame = _starArray[oneI][oneJ]->getSpriteFrame();
		_starArray[oneI][oneJ]->setSpriteFrame(_starArray[twoI][twoJ]->getSpriteFrame());
		_starArray[twoI][twoJ]->setSpriteFrame(tempFrame);

		++count;
	}
	NotificationCenter::getInstance()->postNotification(PROP_COMPLATE);
}

bool StarMatrix::getSelectedArrayAndJudege(Star* star){
	freshenStarMatrix();
	_selectStarArray.push_back(star);
	star->setIsSelected(true);
	//һ����ʱ�Ķ��У�����������������������
	std::queue<Star*> tempStarQueue;
	//std::queue<Star*>::iter tempStarIter
	tempStarQueue.push(star);

	while (tempStarQueue.size() != 0){
		auto tempStar = tempStarQueue.front();
		int indexI = tempStar->getRowIndex();
		int indexJ = tempStar->getColIndex();
		//��ʼ���������ĸ�������ж�
		//��
		//�ж������ߣ��ǲ��ǿ��Ի�ȡ��star
		int nextI = indexI + 1;
		int nextJ = indexJ;
		if (nextI<_rowNum&&_starArray[nextI][nextJ] != nullptr){
			//�ж��Ƿ��Ѿ��ڶ��������˺Ͷ��ߵ���ɫ�Ƿ�һ����
			auto temp = _starArray[nextI][nextJ];
			if (temp->getIsSelected() == false && _starArray[indexI][indexJ]->getCateGory() == temp->getCateGory()){
				//���û�б����뵽�������У�������ɫ��ͬ�Ļ���
				tempStarQueue.push(temp);
				_selectStarArray.push_back(temp);
				temp->setIsSelected(true);
			}
		}
		//��
		nextI = indexI - 1;
		nextJ = indexJ;
		if (nextI >= 0 && _starArray[nextI][nextJ] != nullptr){
			//�ж��Ƿ��Ѿ��ڶ��������˺Ͷ��ߵ���ɫ�Ƿ�һ����
			auto temp = _starArray[nextI][nextJ];
			if (temp->getIsSelected() == false && _starArray[indexI][indexJ]->getCateGory() == temp->getCateGory()){
				//���û�б����뵽�������У�������ɫ��ͬ�Ļ���
				tempStarQueue.push(temp);
				_selectStarArray.push_back(temp);
				temp->setIsSelected(true);
			}
		}
		//��
		nextI = indexI;
		nextJ = indexJ - 1;
		if (nextJ >= 0 && _starArray[nextI][nextJ] != nullptr){
			//�ж��Ƿ��Ѿ��ڶ��������˺Ͷ��ߵ���ɫ�Ƿ�һ����
			auto temp = _starArray[nextI][nextJ];
			if (temp->getIsSelected() == false && _starArray[indexI][indexJ]->getCateGory() == temp->getCateGory()){
				//���û�б����뵽�������У�������ɫ��ͬ�Ļ���
				tempStarQueue.push(temp);
				_selectStarArray.push_back(temp);
				temp->setIsSelected(true);
			}
		}
		//��
		nextI = indexI;
		nextJ = indexJ + 1;
		if (nextJ<_colNum&& _starArray[nextI][nextJ] != nullptr){
			//�ж��Ƿ��Ѿ��ڶ��������˺Ͷ��ߵ���ɫ�Ƿ�һ����
			auto temp = _starArray[nextI][nextJ];
			if (temp->getIsSelected() == false && _starArray[indexI][indexJ]->getCateGory() == temp->getCateGory()){
				//���û�б����뵽�������У�������ɫ��ͬ�Ļ���
				tempStarQueue.push(temp);
				_selectStarArray.push_back(temp);
				temp->setIsSelected(true);
			}
		}

		//��һ������������Ҷ��Ѿ������ˣ����԰������ӱ����Ķ���������������
		//Ȼ��ѭ��������ֱ����������Ѿ�����Ϊֹ��
		tempStarQueue.pop();

	}

	if (_selectStarArray.size() <= 1){
		return false;
	}
	else{
		return true;
	}
}
void StarMatrix::getSelectedStar(Star* star){
	//���ܻ�ѡ�������ģ�������Ҫ�������ĸ���С�ˡ�
	bool condition =  getSelectedArrayAndJudege(star);
	//log("the select  array size  = %d",_selectStarArray.size());
	//demo�Ŵ�����ѡ�еľ���
	if (!condition){
		for (auto const temp : _selectStarArray){
			temp->setIsSelected(false);
		}
		_selectStarArray.clear();
	}
	else{
		MusicManagement::getInstance()->playStarPress();
		for (auto const temp : _selectStarArray){
			//temp->setScale(1.05f);
			auto sequence = Sequence::create(ScaleTo::create(0.25f, 0.8f),
				ScaleTo::create(0.25f, 1.0f), nullptr);
			temp->runAction(RepeatForever::create(sequence));
		}
	}
	
}

int StarMatrix::getScoreByStarNumber(int num){
	return num*num * 5;
}
void StarMatrix::deleteSelectedStar(){
	//��ʼ�����е����Ƕ�������
	//����������������Ǹ���
	MusicManagement::getInstance()->playStarRemove();
	int score = getScoreByStarNumber(_selectStarArray.size());
	if (MyUserData::getInstance()->getIsChallenge()){
		challengeGameLayer->updateTargetScore(score);
	}
	else{
		gameLayer->updateTargetScore(score);
	}
	
	encourageLabel(_selectStarArray.size());
	for (auto temp : _selectStarArray){
		temp->stopAllActions();
		//��vector�е����ݸ����nullptr�ſ��ԡ���Ȼ��Ȼ��ɾ���ˣ������ڻ�����ָ��ָ����һ���ڴ棬���Ծͻ����
		_starArray[temp->getRowIndex()][temp->getColIndex()] = nullptr;
		//���һ���̻�������Ч��
		
		auto* fire = ParticleExplosion::createWithTotalParticles(10);
		auto image = TextureCache::getInstance()->addImage("star.png");
		fire->setTexture(image);
		fire->setLife(1.0f);
		fire->setStartSize(30.0f);
		fire->setEndSize(1.0f);
		/*fire->setStartColor(temp->getColor());
		fire->setEndColor(Color4F(0.0f, 0.0f, 1.0f, 1.0f));*/
		fire->setPosition(temp->getPosition());
		fire->runAction(Sequence::create(DelayTime::create(1.0f),
			RemoveSelf::create(), nullptr));
		this->addChild(fire);
		//Texture2D* image = 

		temp->removeFromParent();
		//temp = nullptr;
	}
	_selectStarArray.clear();
	
	adjustStarMatrix();

	starExistRemove();
	//log("the selectStarArray size  %d  ",_selectStarArray.size());
}

void StarMatrix::adjustStarMatrix(){
	//ÿ�ζ�Ҫ�� λ�ý����ƶ���
	//log("adjust");
	//�з����ϵ��ƶ�
	//��ÿһ�д��µ��Ͻ��м��
	for (int j = 0; j < _colNum; ++j){
		//�ҵ��ж���һ�����������ж��ٿ��С�
		int rowOffset = 0;
		for (int i = 0; i <_rowNum; ++i){
			//�����ǰ���λ��Ϊ��
			if (_starArray[i][j] == nullptr){
				++rowOffset;
			}//�����Ϊ�յĻ����������ƶ���ָ���ľ��룬Ȼ��������滻һ�¡�
			else{
				//_starArray[i][j]
				//�˶��ľ���
				if (rowOffset == 0){
					continue;
				}
				float distanceY = Star::STAR_WIDTH*rowOffset;
				float time = distanceY / _moveSpeed;
				//����һ��λ��
				//��ÿһ�н��м�⣬�仯����i������i��Ҫ�ı䡣
				int tempJ = j;
				int tempI = i - rowOffset;
				//log("hang :  i = %d     j = %d", tempI, tempJ);
				//_starArray[tempI][tempJ] = _starArray[i][j];
				//��£�������Ҫע��һ�£�������Ҫ�����к��У���Ϊ���жϵ�ʱ����Ҫ�õ������Ȼ�Ļ�����õ�����֮ǰ��
				//��ô�����ֵ��ڿ��ˣ��ͻᱨ��
				//һ��Ҫע����ǣ�һ��Ҫ����������������ݣ�����������
				//��Ҫֱ�Ӱ�Ŀ��ĸ��滻�ˣ���Ϊ������offsetΪ��
				std::swap(_starArray[tempI][tempJ], _starArray[i][j]);
				_starArray[tempI][tempJ]->setRowAndColumn(tempI, tempJ);

				_starArray[tempI][tempJ]->runAction(MoveBy::create(time, Vec2(0, -distanceY)));
			}
		}
	}
	//log("adjust exit");
	//�з����ϵ��ƶ�
	//��һ����ȫΪ�յ�ʱ��ſ��Խ����ƶ���
	int colOffset = 0;
	for (int j = 0; j < _colNum; ++j){
		//һ��ȫ����û���ˣ��ſ���
		bool notOne = true;
		//���һ����ʲô��û�У�ȫ�����ǿյĻ�
		for (int i = 0; i < _rowNum; ++i){
			if (_starArray[i][j] != nullptr){
				notOne = false;
			}
		}
		if (notOne){
			++colOffset;
		}
		for (int i = 0; i < _rowNum; ++i){
			if (_starArray[i][j] != nullptr&&colOffset>0){
				float distanceX = Star::STAR_WIDTH*colOffset;
				float time = distanceX / _moveSpeed;

				//����������Ƚ�����Ȼ����ִ�ж�������Ȼ�Ļ������ﻹ��ִ�ж����������е��ж��Ѿ���ʼ��
				//������õķ������Ƚ��������ƶ�

				int tempJ = j - colOffset;
				int tempI = i;
				//log("lie : i = %d     j = %d", tempI, tempJ);
				std::swap(_starArray[tempI][tempJ], _starArray[i][j]);
				_starArray[tempI][tempJ]->setRowAndColumn(tempI, tempJ);

				_starArray[tempI][tempJ]->runAction(MoveBy::create(time, Vec2(-distanceX, 0)));
			}
		}
	}

	if (MyUserData::getInstance()->getIsChallenge()){
		challengeModeProduceMatrix();
	}
}
void StarMatrix::randomProduceStarMatrix(){
	for (int i = 0; i < _rowNum; ++i){
		std::vector<Star*> tempVector;
		for (int j = 0; j < _colNum; ++j){

			Star::STAR_CATEGORY category = (Star::STAR_CATEGORY)random(1, Star::STAR_CATEGORY_NUM);
			Star* star = Star::create(category);
			star->setPosition(getPositionByIndex(i, j));
			star->setRowAndColumn(i, j);
			this->addChild(star);
			tempVector.push_back(star);
		}
		_starArray.push_back(tempVector);
	}
}
void StarMatrix::initStarMatrix(){

	if (MyUserData::getInstance()->getIsChallenge()){
		randomProduceStarMatrix();
		return;
	}
	if (MyUserData::getInstance()->getIsContinue()&&MyUserData::getInstance()->getIsFirstCome()){
		loadToLocal();
		MyUserData::getInstance()->setIsFirstCome(false);
	}
	else{
		randomProduceStarMatrix();
	}
}
void StarMatrix::removeSelectBox(Ref* data){
	if (_selectBG!=nullptr){
		_selectBG->removeFromParent();
		_selectBG = nullptr;
	}
}

void StarMatrix::starExistRemove(){
	bool isExist = false;
	for (int i = 0; i < _rowNum;++i){
		for (int j = 0; j < _colNum&&!isExist;++j){
			if (_starArray[i][j]!=nullptr){

				bool condition = getSelectedArrayAndJudege(_starArray[i][j]);
				//��Ҫ�������������
				for (auto temp:_selectStarArray){
					temp->setIsSelected(false);
				}
				_selectStarArray.clear();
				//��������
				if (condition){
					isExist = true;	
					break;
				}
			}
		}
		//������ھ������ˡ�
		if (isExist){
			break;
		}
	}
	if (!isExist){
		log("not  exist ");
		
		//������սģʽ�Ļ�
		if (!MyUserData::getInstance()->getIsChallenge()){
			_eventDispatcher->removeAllEventListeners();
			countRemainingStarNum();
			schedule(schedule_selector(StarMatrix::removeRemainingStar), 0.1f);
		}
		
	}
	else{
		log("exist  ");
	}
}

void StarMatrix::countRemainingStarNum(){
	int count = 0;
	for (int i = 0; i < _rowNum; ++i){
		for (int j = 0; j < _colNum; ++j){
			if (_starArray[i][j] != nullptr){
				++count;
			}
		}
	}
	_remainingCount = count;
}
void StarMatrix::removeRemainingStar(float dt){
	//��û�����������Ƕ���������Ȼ�����һ��������
	for (int i = _rowNum-1; i >=0; --i){
		for (int j = 0; j < _colNum;++j){
			if (_starArray[i][j]!=nullptr){
				
				MusicManagement::getInstance()->playStarRemove();

				auto* fire = ParticleExplosion::createWithTotalParticles(10);
				auto image = TextureCache::getInstance()->addImage("star.png");
				fire->setTexture(image);
				fire->setLife(1.0f);
				fire->setStartSize(30.0f);
				fire->setEndSize(1.0f);
				fire->setPosition(_starArray[i][j]->getPosition());
				fire->runAction(Sequence::create(DelayTime::create(1.0f),
					RemoveSelf::create(), nullptr));
				this->addChild(fire);
				
				_starArray[i][j]->removeFromParent();
				_starArray[i][j] = nullptr;
				return;
				
			}
		}
	}
	
	unschedule(schedule_selector(StarMatrix::removeRemainingStar));
	scheduleOnce([=](float dt){
		int score = 2000 - _remainingCount * 5;
		if (MyUserData::getInstance()->getIsChallenge()){
			/*if (score>0){
				challengeGameLayer->updateTargetScore(score);
			}*/
			challengeGameLayer->gameComplate();
		}
		else{
			if (score>0){
				gameLayer->updateTargetScore(score);
			}
			gameLayer->gameComplate();
		}
		
	}, 1.0f, "anyword");
}

void StarMatrix::saveToLocal(){
	string path = "";
	string filename = STAR_MATRIX_FILENAME;
	path = FileUtils::getInstance()->getWritablePath() + filename;
	ofstream output(path.c_str(),ios::out);
	
	if (!output.is_open()){
		MessageBox("file open file","waring");
	}
	if (output.is_open()){
		//
		for (int i = 0; i < _rowNum;++i){
			for (int j = 0; j < _colNum;++j){
				if (_starArray[i][j]==nullptr){
					output << 0 << " ";
				}
				else{
					output << _starArray[i][j]->getCateGory() << "  ";
					//tempV.push_back();
				}
			}
			output << "\n";
		}
	}
	output.close();
	//fclose(fp);
}

void StarMatrix::loadToLocal(){
	string path = "";
	string filename = STAR_MATRIX_FILENAME;
	path = FileUtils::getInstance()->getWritablePath() + filename;
	////[4] ��ȡ��������������ͷ����������
	//log("row %d ", csv.getRowCount());
	//log("col %d ", csv.getColumnCount());
	ifstream input(path.c_str(),ios::in);
	for (int i = 0; i < _rowNum;++i){
		std::vector<Star*> tempVector;
		//log("hello ");
		for (int j = 0; j < _colNum;++j){
			int status = 0;
			input >> status;
			if (status==0){
				tempVector.push_back(nullptr);
			}
			else{
				Star::STAR_CATEGORY category = (Star::STAR_CATEGORY)status;
				Star* star = Star::create(category);
				star->setPosition(getPositionByIndex(i, j));
				star->setRowAndColumn(i, j);
				this->addChild(star);
				tempVector.push_back(star);
			}
		}
		_starArray.push_back(tempVector);
	}
	input.close();
}

void StarMatrix::encourageLabel(int num){
	if (num<3){
		return;
	}
	if (num>=11){
		num = 11;
	}
	num = num - 2;
	MusicManagement::getInstance()->playEncourageEffect(num);
	std::string filename = StringUtils::format("texture/tips_%d.png",num);
	auto spr = Sprite::create(filename);
	spr->setPosition(Vec2(_winSize.width/2,_winSize.height*0.7));
	spr->runAction(Sequence::create(Blink::create(1.0,3),ScaleTo::create(0.5f,0.0f),RemoveSelf::create(),nullptr));
	this->addChild(spr,2);
}
bool StarMatrix::init(){
	if (!Node::init()){
		return false;
	}
	//��ʼ������
	log("wtf");
	initData();
	initStarMatrix();
	return true;
}

void StarMatrix::challengeModeProduceMatrix(){
	for (int i = 0; i < _rowNum;++i){
		for (int j = 0; j < _colNum;++j){
			if (_starArray[i][j]==nullptr){
				Star::STAR_CATEGORY category = (Star::STAR_CATEGORY)random(1, Star::STAR_CATEGORY_NUM);
				Star* star = Star::create(category);
				Vec2 targetLocation = getPositionByIndex(i, j);
				star->setPosition(Vec2(targetLocation.x,targetLocation.y+Star::STAR_HEIGHT*5));
				star->setRowAndColumn(i, j);
				//float time = targetLocation.distance(star->getPosition()) / _moveSpeed;
				star->runAction(Sequence::create(MoveTo::create(0.2f,targetLocation), CallFunc::create([=](){
					_starArray[i][j] = star;
				}), nullptr));
				this->addChild(star);
			}
		}
	}
}