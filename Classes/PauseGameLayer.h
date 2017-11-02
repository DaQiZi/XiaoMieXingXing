#ifndef __PAUSE_GAME_LAYER_H
#define __PAUSE_GAME_LAYER_H
#include"cocos2d.h"
using namespace cocos2d;
class GameLayer;
//class ChallengeGameLayer;
class PauseGameLayer : public LayerColor{
public:
	void initData();
	CREATE_FUNC(PauseGameLayer);
	virtual bool init();
	void initBG();
	//void saveToLocal();
public:
	static GameLayer* gameLayer;
	//static ChallengeGameLayer* challengeGameLayer;
private:
	Size _winSize;
	//int _costDiamond;
};

#endif