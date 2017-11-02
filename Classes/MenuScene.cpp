#include"MenuScene.h"
#include"MenuLayer.h"

bool MenuScene::init(){
	if (!Scene::init()){
		return false;
	}
	auto layer = MenuLayer::create();
	this->addChild(layer);

	return true;
}