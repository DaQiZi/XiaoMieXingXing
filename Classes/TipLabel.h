#ifndef _TIP_LABEL_H_
#define _TIP_LABEL_H_
#include"cocos2d.h"
using namespace cocos2d;
class TipLabel :public Node{
public:
	void initData();
	static TipLabel* create(int level, int score);
	virtual bool init(int level,int socre);
private:
	Size _winSize;
};
#endif