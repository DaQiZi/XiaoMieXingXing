#ifndef __GAME_OVER_LAYER_H
#define __GAME_OVER_LAYER_H
#include"cocos2d.h"
using namespace cocos2d;
class GameOverLayer : public LayerColor{
public:
	void initData();
	CREATE_FUNC(GameOverLayer);
	virtual bool init();
	void initBG();
private:
	Size _winSize;
	int _costDiamond;
};

#endif