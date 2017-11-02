#ifndef __STORE_LAYER_H
#define __STORE_LAYER_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class StoreLayer : public LayerColor{
public:
	void initData();
	CREATE_FUNC(StoreLayer);
	virtual bool init();
	void initBG();
private:
	Size _winSize;
};

#endif