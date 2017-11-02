
#include"ui/CocosGUI.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"GameOverLayer.h"
#include"MyUserData.h"
#include"MusicManagement.h"
using namespace ui;
bool GameOverLayer::init(){

	if (!LayerColor::initWithColor(Color4B::GRAY)){
		return false;
	}
	initData();
	this->setContentSize(_winSize);
	this->setOpacity(128.0f);
	initBG();
	return true;
}

void GameOverLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
	_costDiamond = 20;
}

void GameOverLayer::initBG(){
	//修改数据。
	MyUserData::getInstance()->setIsCoutinue(false);
	MyUserData::getInstance()->setIsFirstCome(true);

	auto stopAction = Director::getInstance()->getActionManager()->pauseAllRunningActions();
	auto stopSchedule = Director::getInstance()->getScheduler()->pauseAllTargets();

	/*auto GameOverLayer = LayerColor::create(Color4B::GRAY, _winSize.width, _winSize.height);
	GameOverLayer->setOpacity(128);
	this->addChild(GameOverLayer);*/

	//添加一个触摸吞噬
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Ref* sender){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Sprite* bg = Sprite::create("texture/message_bg_over.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(bg);
	Size size = bg->getContentSize();
	auto btnYes = Button::create("texture/message_b_yes1.png", "texture/message_b_yes2.png");
	btnYes->addTouchEventListener([stopAction, stopSchedule,this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MusicManagement::getInstance()->playBtnPress();
			if (MyUserData::getInstance()->getDiamonds()>_costDiamond){
				Director::getInstance()->getActionManager()->resumeTargets(stopAction);
				Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
				MyUserData::getInstance()->setDiamonds(MyUserData::getInstance()->getDiamonds() - _costDiamond);
				auto scene = GameScene::create();
				Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
			}
			else{
				log("no diamonds");
			}
		}
	});
	
	btnYes->setPosition(Vec2(size.width*0.3f,size.height*0.2f));
	bg->addChild(btnYes);

	auto btnNo = Button::create("texture/message_b_no1.png", "texture/message_b_no2.png");
	btnNo->addTouchEventListener([stopAction, stopSchedule](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){

			MusicManagement::getInstance()->playBtnPress();
			Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
			//分数清除，关卡清除

			MyUserData::getInstance()->setCurrentLevel(1);
			MyUserData::getInstance()->setCurrentScore(0);
			//MyUserData::getInstance()->
			auto scene = MenuScene::create();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
		}
	});

	btnNo->setPosition(Vec2(size.width*0.7f, size.height*0.2f));
	bg->addChild(btnNo);


}