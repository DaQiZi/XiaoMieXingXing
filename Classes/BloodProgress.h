#ifndef _BLOOD_PROGRESS_H_
#define _BLOOD_PROGRESS_H_
#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class BloodProgress : public Node{


public:
	/*BloodProgress();
	void setBackgroundTexture(const char* name);
	void setForegroundTexture(const char* name);
	void setTotalBlood(float blood);
	void setNowBlood(float blood);

	float getTotalBlood();
	float getNowBlood();*/
	static BloodProgress* create(std::string bar,std::string bg,float total,float now);
	//CREATE_FUNC(BloodProgress);
	virtual bool init(std::string bar, std::string bg, float total, float now);
	void initData();
	void changeProgress(float blood);
	void changeContentSize(Size size);
	float getNowBlood();
private:
	LoadingBar* _bloodBG;
	LoadingBar* _bloodBar;
	float _totalBlood;
	float _nowBlood;
	//float _scale;
	//Sprite* bloodRrogress;
};


#endif