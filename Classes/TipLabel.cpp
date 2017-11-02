#include"TipLabel.h"

void TipLabel::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
}

bool TipLabel::init(int level, int socre){

	if (!Node::init()){
		return false;
	}
	initData();
	auto levelLabel = Label::createWithBMFont("fonts/font.fnt",StringUtils::format("Level:%d",level));
	levelLabel->setPosition(Vec2(0,100));
	this->addChild(levelLabel);
	auto scoreLabel = Label::createWithBMFont("fonts/font.fnt", StringUtils::format("TargetScore:%d", socre));
	scoreLabel->setPosition(Vec2(0,0));
	this->addChild(scoreLabel);

	return true;
}

TipLabel* TipLabel::create(int level, int score){
	TipLabel* tip = new TipLabel();
	if (tip&&tip->init(level,score)){
		tip->autorelease();
		return tip;
	}
	CC_SAFE_DELETE(tip);
	return tip;
}