#ifndef __CONTINUE_GAME_LAYER_H
#define __CONTINUE_GAME_LAYER_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class ContinueGameLayer : public LayerColor{
public:
	void initData();
	CREATE_FUNC(ContinueGameLayer);
	virtual bool init();
	void initBG();
private:
	Size _winSize;
};

#endif