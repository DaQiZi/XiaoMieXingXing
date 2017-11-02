#include"MyUserData.h"
//MyUserData* MyUserData::_myuserData = nullptr;
const std::string MyUserData::IS_CONTINUE = "IS_CONTINUE";
const std::string MyUserData::CURRETN_SOCRE = "CURRETN_SOCRE";
const std::string MyUserData::CURRENT_LEVEL="CURRENT_LEVEL";
const std::string MyUserData::STAR_DIAMONDS="STAR_DIAMONDS";
const std::string MyUserData::HIGHEST_SCORE = "HIGHEST_SCORE";

const std::string MyUserData::PROP_BOOM_NUM = "PROP_BOOM_NUM";
const std::string MyUserData::PROP_PAINT_NUM = "PROP_PAINT_NUM";
const std::string MyUserData::PROP_TRANS_NUM = "PROP_TRANS_NUM";
const std::string MyUserData::PROP_STICK_NUM = "PROP_STICK_NUM";
MyUserData* MyUserData::getInstance(){
	static MyUserData myuserData;
	//if (_myuserData==nullptr){
	//	_myuserData = new MyUserData();
	//	//return myuserData;
	//}
	return &myuserData;
}


MyUserData::MyUserData()
{
	//从内存中读取。
	auto user = UserDefault::getInstance();
	_diamonds = user->getIntegerForKey(STAR_DIAMONDS.c_str(),0);
	_currentscore = user->getIntegerForKey(CURRETN_SOCRE.c_str(),0);
	_currentLevel = user->getIntegerForKey(CURRENT_LEVEL.c_str(),1);
	_highestScore = user->getIntegerForKey(HIGHEST_SCORE.c_str(),0);
	_targetScore = _currentLevel*1000;
	//_diamonds = 10;

	_propBoomNum = user->getIntegerForKey(PROP_BOOM_NUM.c_str(),20);
	_propPaintNum = user->getIntegerForKey(PROP_PAINT_NUM.c_str(),20);
	_propStickNum = user->getIntegerForKey(PROP_STICK_NUM.c_str(),20);
	_propTransNum = user->getIntegerForKey(PROP_TRANS_NUM.c_str(),20);

	_isContinue = UserDefault::getInstance()->getBoolForKey(MyUserData::IS_CONTINUE.c_str());
	_isFirstCome = true;
	_isChallenge = false;
}

MyUserData::~MyUserData()
{
	
	//log("...................");
}

int MyUserData::getTargetScore(){

	if (_currentLevel==1){
		return 1000;
	}
	else{
		return (_currentLevel / 10) * 1000 + 3000 * (_currentLevel-1);
	}
	
}


void MyUserData::saveData(){
	auto user = UserDefault::getInstance();
	user->setBoolForKey(MyUserData::IS_CONTINUE.c_str(), _isContinue);
	user->setIntegerForKey(MyUserData::CURRETN_SOCRE.c_str(), _currentscore);
	user->setIntegerForKey(MyUserData::CURRENT_LEVEL.c_str(), _currentLevel);
	user->setIntegerForKey(MyUserData::STAR_DIAMONDS.c_str(), _diamonds);
	user->setIntegerForKey(MyUserData::PROP_BOOM_NUM.c_str(), _propBoomNum);
	user->setIntegerForKey(MyUserData::PROP_PAINT_NUM.c_str(), _propPaintNum);
	user->setIntegerForKey(MyUserData::PROP_STICK_NUM.c_str(), _propStickNum);
	user->setIntegerForKey(MyUserData::PROP_TRANS_NUM.c_str(), _propTransNum);
	user->setIntegerForKey(MyUserData::HIGHEST_SCORE.c_str(), _highestScore);
}
//MyUserData::MyUserData(const MyUserData& data){
//
//}
//MyUserData MyUserData::operator=(const MyUserData& data){
//	return 
//}