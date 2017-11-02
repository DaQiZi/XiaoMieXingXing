#include"GameScene.h"
#include"GameLayer.h"
#include"PauseGameLayer.h"
#include"MyUserData.h"
#include"ChallengeGameLayer.h"
bool GameScene::init(){
	if (!Scene::init()){
		return false;
	}
	if (MyUserData::getInstance()->getIsChallenge()){
		auto layer = ChallengeGameLayer::create();
		this->addChild(layer);
		//PauseGameLayer::gameLayer = layer;
	}
	else{
		auto layer = GameLayer::create();
		this->addChild(layer);
		PauseGameLayer::gameLayer = layer;
	}
	
	return true;
}