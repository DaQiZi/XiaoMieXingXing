
#include"ui/CocosGUI.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"ChallengeGameOverLayer.h"
#include"MyUserData.h"
#include"MusicManagement.h"
using namespace ui;

ChallengeGameOverLayer* ChallengeGameOverLayer::create(int highScore, int score){
	ChallengeGameOverLayer* star = new ChallengeGameOverLayer();
	if (star&&star->init(highScore, score)){
		star->autorelease();
		return star;
	}
	CC_SAFE_DELETE(star);
	return star;
}
bool ChallengeGameOverLayer::init(int highScore, int score){

	if (!LayerColor::initWithColor(Color4B::GRAY)){
		return false;
	}
	initData();
	this->setContentSize(_winSize);
	this->setOpacity(128.0f);
	if (highScore>=score){
		initFailBG(highScore,score);
	}
	else{
		MyUserData::getInstance()->setHighestScore(score);
		initWinBG();
	}
	return true;
}

void ChallengeGameOverLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
	_costDiamond = 20;
	
}

void ChallengeGameOverLayer::initWinBG(){
	//修改数据。
	/*MyUserData::getInstance()->setIsCoutinue(false);
	MyUserData::getInstance()->setIsFirstCome(true);
*/
	MusicManagement::getInstance()->playChallengeSuccess();

	auto stopAction = Director::getInstance()->getActionManager()->pauseAllRunningActions();
	auto stopSchedule = Director::getInstance()->getScheduler()->pauseAllTargets();

	/*auto ChallengeGameOverLayer = LayerColor::create(Color4B::GRAY, _winSize.width, _winSize.height);
	ChallengeGameOverLayer->setOpacity(128);
	this->addChild(ChallengeGameOverLayer);*/

	//添加一个触摸吞噬
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Ref* sender){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Sprite* bg = Sprite::create("texture/message_bg_succ.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(bg);
	Size size = bg->getContentSize();
	auto btnYes = Button::create("texture/message_b_chal1.png", "texture/message_b_chal2.png");
	btnYes->addTouchEventListener([stopAction, stopSchedule,this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MusicManagement::getInstance()->playBtnPress();
			Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);

			auto scene = GameScene::create();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
		}
	});
	
	btnYes->setPosition(Vec2(size.width*0.3f,size.height*0.2f));
	bg->addChild(btnYes);

	auto btnNo = Button::create("texture/message_b_chal3.png", "texture/message_b_chal4.png");
	btnNo->addTouchEventListener([stopAction, stopSchedule](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MusicManagement::getInstance()->playBtnPress();
			Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
			//分数清除，关卡清除

			//MyUserData::getInstance()->
			auto scene = MenuScene::create();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
		}
	});

	btnNo->setPosition(Vec2(size.width*0.7f, size.height*0.2f));
	bg->addChild(btnNo);

}

void ChallengeGameOverLayer::initFailBG(int highScore, int score){
	MusicManagement::getInstance()->playLevelFail();

	auto stopAction = Director::getInstance()->getActionManager()->pauseAllRunningActions();
	auto stopSchedule = Director::getInstance()->getScheduler()->pauseAllTargets();

	/*auto ChallengeGameOverLayer = LayerColor::create(Color4B::GRAY, _winSize.width, _winSize.height);
	ChallengeGameOverLayer->setOpacity(128);
	this->addChild(ChallengeGameOverLayer);*/

	//添加一个触摸吞噬
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Ref* sender){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Sprite* bg = Sprite::create("texture/message_bg_fail.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(bg);
	Size size = bg->getContentSize();

	auto highScoreLabel = Label::createWithCharMap("fonts/num4.png",19,26,'0');
	highScoreLabel->setPosition(Vec2(size.width*0.6f,size.height*0.5f));
	highScoreLabel->setString(StringUtils::format("%d",highScore));
	bg->addChild(highScoreLabel);

	auto scoreLabel = Label::createWithCharMap("fonts/num4.png", 19, 26, '0');
	scoreLabel->setPosition(Vec2(size.width*0.6f, size.height*0.4f));
	scoreLabel->setString(StringUtils::format("%d",score));
	bg->addChild(scoreLabel);

	//Size bgsize = bg->getContentSize();
	auto btnYes = Button::create("texture/message_b_chal1.png", "texture/message_b_chal2.png");
	btnYes->addTouchEventListener([stopAction, stopSchedule, this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);

			auto scene = GameScene::create();
			Director::getInstance()->replaceScene(scene);
		}
	});

	btnYes->setPosition(Vec2(size.width*0.3f, size.height*0.2f));
	bg->addChild(btnYes);

	auto btnNo = Button::create("texture/message_b_chal3.png", "texture/message_b_chal4.png");
	btnNo->addTouchEventListener([stopAction, stopSchedule](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
			//分数清除，关卡清除

			//MyUserData::getInstance()->
			auto scene = MenuScene::create();
			Director::getInstance()->replaceScene(scene);
		}
	});

	btnNo->setPosition(Vec2(size.width*0.7f, size.height*0.2f));
	bg->addChild(btnNo);
}