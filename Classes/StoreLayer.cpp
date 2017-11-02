#include"StoreLayer.h"
#include"MyUserData.h"
#include"MusicManagement.h"
bool StoreLayer::init(){

	if (!LayerColor::initWithColor(Color4B::GRAY)){
		return false;
	}
	initData();
	this->setContentSize(_winSize);
	this->setOpacity(128.0f);
	initBG();
	return true;
}

void StoreLayer::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
}

void StoreLayer::initBG(){
	
	/*auto stopAction = Director::getInstance()->getActionManager()->pauseAllRunningActions();
	auto stopSchedule = Director::getInstance()->getScheduler()->pauseAllTargets();*/

	/*auto storeLayer = LayerColor::create(Color4B::GRAY, _winSize.width, _winSize.height);
	storeLayer->setOpacity(128);
	this->addChild(storeLayer);*/

	//Ìí¼ÓÒ»¸ö´¥ÃþÍÌÊÉ
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Ref* sender){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Sprite* bg = Sprite::create("texture/mall_bg.png");
	bg->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(bg);

	Button* closeitem = Button::create("btn/mall_close1.png", "btn/mall_close2.png", "");
	closeitem->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		//MusicManagement::getInstance()->playBtnPress();
		//MusicManagement::getInstance()->playBtnPress();
		if (type == Widget::TouchEventType::ENDED){
			//this->menu->setEnabled(true);
			MusicManagement::getInstance()->playBtnPress();
			/*Director::getInstance()->getActionManager()->resumeTargets(stopAction);
			Director::getInstance()->getScheduler()->resumeTargets(stopSchedule);*/
			this->removeFromParent();
		}
		//Director::getInstance()->resume();
	});
	Size size(bg->getContentSize());
	closeitem->setPosition(Vec2(size.width - closeitem->getContentSize().width / 2, size.height - closeitem->getContentSize().height / 2));
	bg->addChild(closeitem);
	//listvie
	auto listview = ListView::create();
	listview->setBounceEnabled(true);
	listview->setContentSize(Size(size.width*0.96, size.height*0.6));
	listview->setAnchorPoint(Vec2(0.5, 0.5));
	listview->setPosition(Vec2(size.width / 2, size.height / 2));
	bg->addChild(listview);
	//add data

	auto diamondsTip = Label::createWithCharMap("fonts/num3.png", 18, 22, '0');
	diamondsTip->setPosition(Size(size.width*0.6f, size.height*0.14f));
	diamondsTip->setString(StringUtils::format("%9d", MyUserData::getInstance()->getDiamonds()));
	bg->addChild(diamondsTip);
	for (int i = 0; i < 6; ++i){
		auto layout = Layout::create();
		auto image = ImageView::create("texture/mall_list_bg.png");
		layout->addChild(image);
		layout->setContentSize(Size(image->getContentSize().width*1.1f, image->getContentSize().height*1.1f));

		Size size = layout->getContentSize();
		image->setPosition(Size(size.width / 2, size.height / 2));
		auto buyLabel = Label::createWithCharMap("fonts/num11.png", 21, 28, '0');
		buyLabel->setString(StringUtils::format("%d", (i + 1) * 100));
		buyLabel->setPosition(Vec2(size.width*0.2, size.height / 2));
		layout->addChild(buyLabel);

		auto giftLabel = Label::createWithCharMap("fonts/num11.png", 21, 28, '0');
		giftLabel->setString(StringUtils::format("%d", (i + 1) * 10));
		giftLabel->setPosition(Vec2(size.width*0.6, size.height / 2));
		layout->addChild(giftLabel);

		auto buybtn = Button::create("btn/mall_buy1.png", "btn/mall_buy2.png");
		buybtn->setPosition(Vec2(size.width*0.85, size.height / 2));
		layout->addChild(buybtn);
		auto buybtnLabel = Label::createWithCharMap("fonts/num11.png", 21, 28, '0');
		buybtnLabel->setString(StringUtils::format("%d", (i + 1)));
		//buybtnLabel->setPosition(Vec2(size.width*0.6, size.height / 2));
		//layout->addChild(giftLabel);
		buybtn->setTitleLabel(buybtnLabel);
		buybtn->addTouchEventListener([i, diamondsTip](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED){
				int money = i + 1;
				int num = (i + 1) * 110;
				MyUserData::getInstance()->addDiamonds(num);
				MusicManagement::getInstance()->playBtnPress();
				diamondsTip->setString(StringUtils::format("%9d", MyUserData::getInstance()->getDiamonds()));
				MyUserData::getInstance()->saveData();
				/*log("you cost  %d  $", money);
				int nextmoney = money&(money-1);
				log("next monty  %d ",nextmoney);*/
			}
		});
		listview->pushBackCustomItem(layout);
	}

}