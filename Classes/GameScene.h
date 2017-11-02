#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H
#include"cocos2d.h"
using namespace cocos2d;
class  GameScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif