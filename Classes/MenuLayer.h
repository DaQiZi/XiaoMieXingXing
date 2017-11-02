#ifndef _MENU_LAYER_H
#define _MENU_LAYER_H
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class  MenuLayer : public Layer{
public:
	virtual bool init();
	void initData();
	void initBG();
	CREATE_FUNC(MenuLayer);
	/////////////////////////////////////
	//�˵������һЩС���溯��
	void storeMenu();
	void continueMenu();
	void helpMenu();
	///////////////////////////////////
private:
	Size _winSize;
	Menu* menu;
};

#endif