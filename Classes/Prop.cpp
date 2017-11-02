#include"Prop.h"
#include"MyUserData.h"
const std::string Prop::FILE_PATH = "texture/";
const int Prop::PROP_NUM = 4;
void Prop::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
	_isSelected = false;

	switch (_propCategory)
	{
	case Prop::PROP_BOOM:
		_propNum = MyUserData::getInstance()->getPropBoomNum();
		_cost = 50;
		break;
	case Prop::PROP_PAINT:
		_propNum = MyUserData::getInstance()->getPropPaintNum();
		_cost = 200;
		break;
	case Prop::PROP_STICK:
		_propNum = MyUserData::getInstance()->getPropStickNum();
		_cost = 20;
		break;
	case Prop::PROP_TRANS:
		_propNum = MyUserData::getInstance()->getPropTransNum();
		_cost = 100;
		break;
	default:
		break;
	}
	//_propNum = 10;

	//_selectProp = nullptr;
}

bool Prop::init(PROP_CATEGORY category){
	if (!Node::init()){
		return false;
	}
	this->_propCategory = category;
	initData();
	//this->initWithSpriteFrameName(this->getImageName(category));
	std::string filename = this->getImageName(category);
	_iconBtn = Sprite::create(filename);
	
	this->setContentSize(_iconBtn->getContentSize());
	_iconBtn->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(_iconBtn);

	_tipLabel = Label::createWithCharMap("fonts/num3.png",18,22,'0');
	_tipLabel->setString(StringUtils::format(":%d",_propNum));
	_tipLabel->setPositionX(this->getContentSize().width);
	this->addChild(_tipLabel);
	
	return true;
}


Prop* Prop::create(PROP_CATEGORY category){

	Prop* prop = new Prop();
	if (prop&&prop->init(category)){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return prop;
}

std::string Prop::getImageName(PROP_CATEGORY category){
	std::string filename = "";
	switch (category)
	{
	case Prop::PROP_BOOM:
		filename = FILE_PATH+"props_bomb.png";
		break;
	case Prop::PROP_PAINT:
		filename = FILE_PATH+"props_paint.png";
		break;
	case Prop::PROP_STICK:
		filename = FILE_PATH+"props_stick.png";
		break;
	case Prop::PROP_TRANS:
		filename = FILE_PATH+"props_trans.png";
		break;
	default:
		break;
	}
	return filename;
}


Prop::PROP_CATEGORY Prop::getCateGory(){
	return _propCategory;
}

void Prop::setIsSelected(bool flag){
	this->_isSelected = flag;
}
bool Prop::getIsSelected(){
	return _isSelected;
}

void Prop::propUsedUp(){
	_propNum -= 1;
	_tipLabel->setString(StringUtils::format(":%d", _propNum));
	switch (_propCategory)
	{
	case Prop::PROP_BOOM:
		MyUserData::getInstance()->setPropBoomNum(MyUserData::getInstance()->getPropBoomNum()-1);
		break;
	case Prop::PROP_PAINT:
		MyUserData::getInstance()->setPropPaintNum(MyUserData::getInstance()->getPropPaintNum() - 1);
		break;
	case Prop::PROP_STICK:
		MyUserData::getInstance()->setPropStickNum(MyUserData::getInstance()->getPropStickNum() - 1);
		break;
	case Prop::PROP_TRANS:
		MyUserData::getInstance()->setPropTransNum(MyUserData::getInstance()->getPropTransNum() - 1);
		break;
	default:
		break;
	}
}