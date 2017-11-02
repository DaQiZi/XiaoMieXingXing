#include "BloodProgress.h"
BloodProgress* BloodProgress::create(std::string bar, std::string bg, float total, float now){
	
	BloodProgress* blood = new BloodProgress();
	if (blood&&blood->init(bar,bg,total,now)){
		blood->autorelease();
		return blood;
	}
	CC_SAFE_DELETE(blood);
	blood = nullptr;
	return blood;
	//Sprite::createWithSpriteFrameName
}

bool BloodProgress::init(std::string bar, std::string bg, float total, float now){
	if (!Node::init()){
		return false;
	}
	_bloodBar = LoadingBar::create(bar);
	this->setContentSize(_bloodBar->getContentSize());
	this->setAnchorPoint(Vec2(0.5,0.5));



	Size size = this->getContentSize();
	_bloodBar->setPosition(Vec2(size.width/2,size.height/2));
	_bloodBar->setPercent(100.0f);
	this->addChild(_bloodBar,1);

	_bloodBG = LoadingBar::create(bg);
	_bloodBG->setPosition(Vec2(size.width / 2, size.height / 2));
	_bloodBG->setPercent(100.0f);
	this->addChild(_bloodBG);

	_totalBlood = total;
	_nowBlood = now;

	return true;
}

void BloodProgress::initData(){
	_bloodBar = nullptr;
	_bloodBG = nullptr;
}

void BloodProgress::changeProgress(float blood){
	_nowBlood -= blood;
	if (_nowBlood<=0.0){
		_nowBlood = 0;
		_bloodBar->setPercent(0);
	}
	else if (_nowBlood>_totalBlood){
		_nowBlood = _totalBlood;
		_bloodBar->setPercent(_nowBlood * 100 / _totalBlood);
	}
	else{
		_bloodBar->setPercent(_nowBlood*100/_totalBlood);
	}
}

void BloodProgress::changeContentSize(Size size){
	//this->setContentSize(size);
	

	_bloodBar->setScale9Enabled(true);
	_bloodBar->setContentSize(size);
	_bloodBG->setScale9Enabled(true);
	_bloodBG->setContentSize(size);
}

float BloodProgress::getNowBlood(){
	return _nowBlood;
}