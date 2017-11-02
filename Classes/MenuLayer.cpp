#include"MenuLayer.h"
#include"GameScene.h"
#include"MyUserData.h"
#include"StoreLayer.h"
#include"ContinueGameLayer.h"
#include"MusicManagement.h"
bool MenuLayer::init(){
	if (!Layer::init()){
		return false;
	}
	initData();
	initBG();
	MusicManagement::getInstance()->playMenuBGMusic();
	return true;
}

void MenuLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize();

	/*string path = "";
	string filename = "MyStar.csv";
	path = FileUtils::getInstance()->getWritablePath()+filename;
	log("%s",path.c_str());
	FILE* fp = fopen(path.c_str(),"w");
	log("hello world");
	if (fp){
		for (int i = 0; i < 3;++i){
			log("......................");
			std::string str = "123,1213,456,456,1234,654\n";
			
			fputs(str.c_str(),fp);
		}
	}
	fclose(fp);*/
	//log("%s",path.c_str());
	////对于csv文件读写的测试
	////string path = "/soft/cocos2d-x-3.4/projects/Demo34/Resources/testCSV.csv";

	////[3] 解析csv文件
	//Csv csv = Csv(path.c_str());

	//////[4] 获取总行数（包含列头）、总列数
	//log("row %d ", csv.getRowCount());
	//log("col %d ", csv.getColumnCount());

	////[5] 获取所有数据（第0行为列头字段）
	// csv.getRowCount() : 数据总行数（包含列头）
	/*for (int i = 0; i < csv.getRowCount(); i++) {
		 //csv[i].size() : 每条数据有多少字段
		log("the size =  %d", csv[i].size());
		for (int j = 0; j < csv[i].size(); j++) {
			log("%s  ",csv[i][j].c_str());
		}
		puts("");
	}*/
}

void MenuLayer::initBG(){
	Sprite*  bg = Sprite::create("cover.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(bg);

	Sprite*  logo = Sprite::create("game_name.png");
	logo->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.8));
	this->addChild(logo);

	MenuItem* startitem = MenuItemImage::create("btn/start_btn_normal.png", "btn/start_btn_press.png", "", [this](Ref* sender){
		log("back");
		MyUserData::getInstance()->setISChallenge(false);
		if (MyUserData::getInstance()->getIsContinue()){
			continueMenu();
		}
		else{
			auto scene = GameScene::create();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f,scene));
		}
		MusicManagement::getInstance()->playBtnPress();
		
	});
	startitem->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.6));


	MenuItem* challengeitem = MenuItemImage::create("btn/challenge_btn_normal.png", "btn/challenge_btn_press.png", "", [this](Ref* sender){
		log("change");
		MusicManagement::getInstance()->playBtnPress();
		MyUserData::getInstance()->setISChallenge(true);
		auto scene = GameScene::create();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));

	});
	challengeitem->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.45f));




	MenuItem* shopitem = MenuItemImage::create("btn/shop_btn_normal.png", "btn/shop_btn_press.png", "",
		[this](Ref* sender){
		//MusicManagement::getInstance()->playBtnPress();
		MusicManagement::getInstance()->playBtnPress();
		log("shop");
		storeMenu();
	});
	shopitem->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.3));
	//startitem->

	MenuItem* exititem = MenuItemImage::create("btn/close_btn_normal.png", "btn/close_btn_press.png", "",
		[this](Ref* sender){
		//MusicManagement::getInstance()->playBtnPress();
		//log("rank");
		//rankMenu();
		MyUserData::getInstance()->saveData();
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		exit(0);
#endif
	}
	);
	exititem->setPosition(Vec2(_winSize.width / 2, _winSize.height*0.18));
	Vec2 location = exititem->getPosition();
	Size size = exititem->getContentSize();
	
	MenuItemToggle* settingitem = MenuItemToggle::createWithCallback([this](Ref* sender){
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

	}, MenuItemImage::create("btn/cover_b5.png", "btn/cover_b6.png"),
		MenuItemImage::create("btn/cover_b6.png", "btn/cover_b5.png"),nullptr);
	settingitem->setPosition(Vec2(location.x + size.width*1.5, location.y));
	if (!MusicManagement::getInstance()->getMusicStatus()){
		settingitem->setSelectedIndex(1);
	}

	MenuItem* helpitem = MenuItemImage::create("btn/help_btn_normal.png", "btn/help_btn_press.png", "",
		[this](Ref* sender){
		//MusicManagement::getInstance()->playBtnPress();
		//log("help");
		//helpMenu();
		MusicManagement::getInstance()->playBtnPress();
		log("help");
		helpMenu();
	}
	);
	helpitem->setPosition(Vec2(location.x - size.width * 1.5, location.y));

	menu = Menu::create(startitem, challengeitem, shopitem, exititem, settingitem, helpitem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}


void MenuLayer::storeMenu(){
	auto layer = StoreLayer::create();
	this->addChild(layer);
}

void MenuLayer::continueMenu(){
	auto layer = ContinueGameLayer::create();
	this->addChild(layer);
}

void MenuLayer::helpMenu(){

	auto layer = LayerColor::create(Color4B::GRAY,_winSize.width,_winSize.height);
	layer->setOpacity(128);
	this->addChild(layer);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Ref* sender){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, layer);


	Sprite* bg = Sprite::create("texture/help_1.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	layer->addChild(bg);

	Button* closeitem = Button::create("btn/mall_close1.png", "btn/mall_close2.png", "");
	closeitem->addTouchEventListener([layer](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			//this->menu->setEnabled(true);
			MusicManagement::getInstance()->playBtnPress();
			/*Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);*/
			layer->removeFromParent();
		}
		//Director::getInstance()->resume();
	});
	Size size(bg->getContentSize());
	closeitem->setPosition(Vec2(size.width - closeitem->getContentSize().width / 2, size.height - closeitem->getContentSize().height / 2));
	bg->addChild(closeitem);
	//listvie
	
}