#include"ChallengeGameLayer.h"
#include"MenuScene.h"
#include"Config.h"
#include"TipLabel.h"
#include"MyUserData.h"
#include"ChallengeGameOverLayer.h"
#include"GameScene.h"
#include"PauseGameLayer.h"
#include"MusicManagement.h"
void ChallengeGameLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize(); 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stars.plist");
	_selectProp = nullptr;

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ChallengeGameLayer::propUseComplate), PROP_COMPLATE, NULL);

	_currentScore = 0;
	//_targetScore = MyUserData::getInstance()->getTargetScore();
	//_currentLevel = MyUserData::getInstance()->getCurrentLevel();
	_diamondsNum = MyUserData::getInstance()->getDiamonds();
	_highestScore = MyUserData::getInstance()->getHighestScore();

	_currentScoreLabel = nullptr;
	//_targetScoreLabel = nullptr;
	//_currentLevelLabel = nullptr;
	
	matrix = nullptr;

	StarMatrix::challengeGameLayer = this;

	_isPass = false;

}
void ChallengeGameLayer::initBG(){
	auto spr_bg = Sprite::create("running_bg.png");
	spr_bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(spr_bg);

	//初始化标签

	auto diamondsSpr = Sprite::create("texture/b_money1.png");
	diamondsSpr->setPosition(Vec2(_winSize.width*0.85f, _winSize.height*0.85f));
	//diamondsSpr->setString(StringUtils::format("%d", _diamondsNumLabel));
	this->addChild(diamondsSpr);
	_diamondsNumLabel = Label::createWithCharMap("fonts/num4.png", 19, 26, '0');
	_diamondsNumLabel->setPosition(diamondsSpr->getPosition());
	_diamondsNumLabel->setString(StringUtils::format("%d", _diamondsNum));
	this->addChild(_diamondsNumLabel);

	//和模式有关的标签的显示
	//关卡标签
	//log("..................");
	//auto levelSpr = Sprite::create("texture/running_level.png");
	//levelSpr->setPosition(Vec2(levelSpr->getContentSize().width,_winSize.height-levelSpr->getContentSize().height));
	//this->addChild(levelSpr);
	////当前的关卡
	//_currentLevelLabel = Label::createWithCharMap("fonts/num4.png",19,26,'0');
	//_currentLevelLabel->setPosition(Vec2(levelSpr->getPositionX()+20,levelSpr->getPositionY()-30));
	//_currentLevelLabel->setString(StringUtils::format("%d",_currentLevel));
	//this->addChild(_currentLevelLabel);
	
	////目标标签
	auto targetSpr = Sprite::create("texture/challenge_max.png");
	targetSpr->setPosition(Vec2(_winSize.width*0.35f,_winSize.height*0.97f));
	this->addChild(targetSpr);
	//目标分数
	_highestScoreLabel = Label::createWithCharMap("fonts/num4.png", 19, 26, '0');
	_highestScoreLabel->setPosition(Vec2(targetSpr->getPositionX() + 100, targetSpr->getPositionY()));
	_highestScoreLabel->setString(StringUtils::format("%d", _highestScore));
	this->addChild(_highestScoreLabel);

	_currentScoreLabel = Label::createWithCharMap("fonts/num4.png", 19, 26, '0');
	_currentScoreLabel->setPosition(Vec2(_winSize.width*0.6f,_winSize.height*0.87f));
	_currentScoreLabel->setString(StringUtils::format("%d", _currentScore));
	this->addChild(_currentScoreLabel);

	pauseBtn = Button::create("btn/b_paused.png","btn/b_resume.png");
	Vec2 location(_winSize.width - pauseBtn->getContentSize().width/2-12,
		_winSize.height-pauseBtn->getContentSize().height/2-5);
	pauseBtn->setPosition(location);
	pauseBtn->addTouchEventListener([this](Ref* sender,Widget::TouchEventType type){
		if (type==Widget::TouchEventType::ENDED){
			//去暂停的界面
			MusicManagement::getInstance()->playBtnPress();
			log("pause");
			pauseMenu();
		}
	});
	this->addChild(pauseBtn);

	//////////////////////////////////////////////////
	//道具的显示
	for (int i = 1; i <= Prop::PROP_NUM;++i){
		Prop* prop = Prop::create((Prop::PROP_CATEGORY)i);
		//prop->setPropNum(my);
		prop->setPosition(Vec2((i-1)*100+60,_winSize.height*0.03f));
		this->addChild(prop);
		_propVector.pushBack(prop);
	}

}

void ChallengeGameLayer::checkLabelStatus(float){
	if (MyUserData::getInstance()->getDiamonds() != _diamondsNum){
		_diamondsNum = MyUserData::getInstance()->getDiamonds();
		_diamondsNumLabel->setString(StringUtils::format("%d", _diamondsNum));
	}
}
void ChallengeGameLayer::pauseMenu(){
	auto layer = PauseGameLayer::create();
	this->addChild(layer);
}

void ChallengeGameLayer::propTouchJudge(Vec2 touch){
	/*if (_selectProp!=nullptr){
		_selectProp->stopAllActions();
		_selectProp->setScale(1.0f);
	}*/
	for (auto const prop : _propVector){
		if (prop->getBoundingBox().containsPoint(touch)){
			//之前选择的不为空，这一次又选择自己，或者选择其他的道具
			//在道具的使用前就要判断，钻石的花费和道具的数量
			//
			if (prop->getPropNum()<=0&&(_diamondsNum-prop->getCost())<=0){
				log("prop num <=0|| _dismondsNum-cost <=0");
				//在不准使用道具的同时，还需要判断是否点击了一个道具然后再点另外一个道具这种情况
				//之前点击过
				if (_selectProp!=nullptr){
					_selectProp->stopAllActions();
					_selectProp->setScale(1.0f);
					_selectProp->setIsSelected(false);
					_selectProp = nullptr;
				}
				break;
			}
			if (_selectProp != nullptr){

				//如果是point的话，要做特殊的处理
				if (_selectProp->getCateGory()==Prop::PROP_CATEGORY::PROP_STICK){
					NotificationCenter::getInstance()->postNotification(REMOVE_SELECT_BOX);
				}
				
				_selectProp->stopAllActions();
				_selectProp->setScale(1.0f);
				_selectProp->setIsSelected(false);
				//如果是点击的是自身
				if (prop==_selectProp){
					_selectProp = nullptr;
				}
				else{
					_selectProp = prop;
					_selectProp->setIsSelected(true);
					auto sequence = Sequence::create(ScaleTo::create(0.25f, 0.8f),
						ScaleTo::create(0.25f, 1.0f), nullptr);
					_selectProp->runAction(RepeatForever::create(sequence));
				}
			}
			else{
				_selectProp = prop;
				_selectProp->setIsSelected(true);
				auto sequence = Sequence::create(ScaleTo::create(0.25f, 0.8f),
					ScaleTo::create(0.25f, 1.0f), nullptr);
				_selectProp->runAction(RepeatForever::create(sequence));
			}
			break;
			//log("select prop ");
		}
	}
}

void ChallengeGameLayer::trasitionLabel(){
	auto tipLabel = Sprite::create("texture/running_ready_go.png");
	tipLabel->setScale(0);
	tipLabel->setPosition(Vec2(_winSize.width/2,_winSize.height/2));
	auto action_1 = ScaleTo::create(1.5f,1.0f);
	auto actionD = DelayTime::create(1.0f);
	auto action_2 = ScaleTo::create(1.0f,0);
	auto action_3 = CallFunc::create([this, tipLabel](){
		produStarMatrixAndAddListener();
		tipLabel->removeFromParent();
	});
	tipLabel->runAction(Sequence::create(action_1, actionD, action_2, action_3, nullptr));
	this->addChild(tipLabel);

	MusicManagement::getInstance()->playGameStart();
}
bool ChallengeGameLayer::init(){
	if (!Layer::init()){
		return false;
	}
	initData();
	initBG();
	trasitionLabel();
	//initStarMatrix();
	//添加一个飘动感觉
	schedule(schedule_selector(ChallengeGameLayer::checkLabelStatus), 1.0f);
	return true;
}

void ChallengeGameLayer::propUseComplate(Ref* data){
	_selectProp->setIsSelected(false);
	_selectProp->stopAllActions();
	_selectProp->setScale(1.0f);
	if (_selectProp->getPropNum()==0){
		_diamondsNum -= _selectProp->getCost();
		_diamondsNumLabel->setString(StringUtils::format("%d", _diamondsNum));
		MyUserData::getInstance()->setDiamonds(_diamondsNum);
	}
	else{
		_selectProp->propUsedUp();
	}
	_selectProp = nullptr;
	log("complate");
}

void ChallengeGameLayer::updateTargetScore(int score){
	_currentScore += score;
	_currentScoreLabel->setString(StringUtils::format("%d",_currentScore));
	changeTimeLoading(score/400.0f);
	//if (_currentScore>=_targetScore&&!_isPass){

	//	auto spr = Sprite::create("texture/running_level_pass.png");
	//	auto action1 = ScaleTo::create(1.5f, 1.5f);
	//	auto action2 = ScaleTo::create(1.0f, 0.5f);
	//	auto action3 = MoveBy::create(1.0f,Vec2(0,230));
	//	spr->setPosition(Vec2(_winSize.width/2,_winSize.height/2));
	//	spr->runAction(Sequence::create(action1,action2,action3,nullptr));
	//	this->addChild(spr);

	//	_isPass = true;
	//}
}

void ChallengeGameLayer::gameComplate(){
	NotificationCenter::getInstance()->removeAllObservers(this);
	auto layer = ChallengeGameOverLayer::create(_highestScore,_currentScore);
	this->addChild(layer);
}

void ChallengeGameLayer::produStarMatrixAndAddListener(){
	//_tipLoading = LoadingBar::create("");
	_tipLoading = BloodProgress::create("texture/challenge_time_line.png","texture/challenge_time_bg.png",60.0f,60.0f);
	_tipLoading->setPosition(Vec2(_winSize.width/2,_winSize.height*0.8f));
	schedule(schedule_selector(ChallengeGameLayer::updateTimeLoading));
	this->addChild(_tipLoading);
	matrix = StarMatrix::create();
	this->addChild(matrix);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* unuse_event)->bool{

		//touch->getDelta();
		//判断是否点击到了道具
		propTouchJudge(touch->getLocation());
		//判断是否点击到了星星矩阵
		//并且把道具的传进去。
		matrix->starTouchJudge(touch->getLocation(), _selectProp);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ChallengeGameLayer::saveToLocal(){
	//防止还没有初始化的时候，就点了返回了，初始化在标签出现之后才出来的。
	//if (matrix!=nullptr){
	//	MyUserData::getInstance()->setIsCoutinue(true);
	//	MyUserData::getInstance()->setIsFirstCome(true);

	//	//MyUserData::getInstance()->setCurrentLevel(_currentLevel);
	//	MyUserData::getInstance()->setCurrentScore(_currentScore);

	//	matrix->saveToLocal();
	//}
	
}

void ChallengeGameLayer::updateTimeLoading(float dt){
	_tipLoading->changeProgress(dt);
	if (_tipLoading->getNowBlood()<=0.0f){
		unschedule(schedule_selector(ChallengeGameLayer::updateTimeLoading));
		gameComplate();
	}
}
void ChallengeGameLayer::changeTimeLoading(float dt){
	
	_tipLoading->changeProgress(-dt);
}