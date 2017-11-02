#ifndef __CHALLENGE_GAME_OVER_LAYER_H
#define __CHALLENGE_GAME_OVER_LAYER_H
#include"cocos2d.h"
using namespace cocos2d;
class ChallengeGameOverLayer : public LayerColor{
public:
	void initData();
	static ChallengeGameOverLayer* create(int highScore,int score);
	virtual bool init(int highScore, int score);
	void initWinBG();
	void initFailBG(int highScore,int score);
private:
	Size _winSize;
	int _costDiamond;
	//bool _isComplate;
};

#endif