
#include"MyUserData.h"
#include"PauseGameLayer.h"
#include"MenuScene.h"
#include"GameLayer.h"
#include"StoreLayer.h"
#include"MusicManagement.h"
GameLayer* PauseGameLayer::gameLayer = nullptr;
//ChallengeGameLayer* PauseGameLayer::challengeGameLayer = nullptr;
bool PauseGameLayer::init(){

	if (!LayerColor::initWithColor(Color4B::GRAY)){
		return false;
	}
	initData();
	this->setContentSize(_winSize);
	this->setOpacity(128.0f);
	initBG();
	return true;
}

void PauseGameLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
	//_costDiamond = 20;
}

void PauseGameLayer::initBG(){
	//修改数据。
	//Director::getInstance()->pause();
	auto stopAction = Director::getInstance()->getActionManager()->pauseAllRunningActions();
	auto stopSchedule = Director::getInstance()->getScheduler()->pauseAllTargets();
	//pauseBtn->setEnabled(false);
	//auto layer = LayerColor::create(Color4B::GRAY, _winSize.width, _winSize.height);
	//layer->setOpacity(128);
	////layer->setPosition(Vec2(_winSize.width/2,_winSize.height/2));
	//this->addChild(layer);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* unuse_event)->bool{
		log("touching .....");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto resumeItem = MenuItemImage::create("btn/pause_b01.png", "btn/pause_b02.png", "", [stopSchedule, stopAction, this](Ref* sender){
		log("resume");
		//Director::getInstance()->resume();
		MusicManagement::getInstance()->playBtnPress();
		Director::getInstance()->getActionManager()->resumeTargets(stopAction);
		Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
		this->removeFromParent();
		//pauseBtn->setEnabled(true);
	});
	auto returnItem = MenuItemImage::create("btn/pause_b11.png", "btn/pause_b12.png", "", [stopSchedule, stopAction,this](Ref* sender){
		log("return");
		//Director::getInstance()->resume();

		Director::getInstance()->getActionManager()->resumeTargets(stopAction);
		Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);
		MusicManagement::getInstance()->playBtnPress();
		//MyUserData::getInstance()->setIsCoutinue(false);
		//MyUserData::getInstance()->setIsFirstCome(true);
		//gameLayer->
		NotificationCenter::getInstance()->removeAllObservers(this->getParent());
		if (!MyUserData::getInstance()->getIsChallenge()){
			gameLayer->saveToLocal();
		}
		this->removeFromParent();
		auto scene = MenuScene::create();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
	});

	MenuItemToggle* musicItem = MenuItemToggle::createWithCallback([this](Ref* sender){
		//MusicManagement::getInstance()->playBtnPress();
		auto item = dynamic_cast<MenuItemToggle*>(sender);
		//根据取得的下标来决定是否暂停音乐
		int index = item->getSelectedIndex();
		MusicManagement::getInstance()->playBtnPress();
		if (index == 0){
			log("music on");
			MusicManagement::getInstance()->resumeMusic();
			MusicManagement::getInstance()->resumeEffect();
		}
		else{
			MusicManagement::getInstance()->stopMusic();
			MusicManagement::getInstance()->stopEffect();
			log("music off");
		}

	}, MenuItemImage::create("btn/pause_b21.png", "btn/pause_b22.png"),
		MenuItemImage::create("btn/pause_b31.png", "btn/pause_b32.png"), nullptr);
	//musicItem->setPosition(Vec2(location.x + size.width*1.5, location.y));
	if (!MusicManagement::getInstance()->getMusicStatus()){
		musicItem->setSelectedIndex(1);
	}

	auto shopItem = MenuItemImage::create("btn/pause_b41.png", "btn/pause_b42.png", "", [this](Ref* sender){
		log("shop");
		MusicManagement::getInstance()->playBtnPress();
		auto layer = StoreLayer::create();
		this->addChild(layer);
	});

	auto bg = Sprite::create("btn/pause_bg.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.6f));
	this->addChild(bg);
	auto menu = Menu::create(resumeItem, returnItem, musicItem, shopItem, nullptr);
	menu->alignItemsVerticallyWithPadding(8);
	menu->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2));
	bg->addChild(menu);

	auto tip = Sprite::create("btn/pause_tip.png");
	tip->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.12f));
	this->addChild(tip);
}
//void PauseGameLayer::saveToLocal(){
//
//}