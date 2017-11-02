#ifndef _PROP_H
#define _PROP_H
#include"cocos2d.h"
using namespace cocos2d;
class  Prop : public Node{
public:
	enum PROP_CATEGORY
	{
		PROP_BOOM = 1,
		PROP_PAINT,
		PROP_STICK,
		PROP_TRANS
	};
	virtual bool init(PROP_CATEGORY category);
	static Prop* create(PROP_CATEGORY category);
	std::string getImageName(PROP_CATEGORY category);
	/*void setRowAndColumn(int row,int col);
	int getRowIndex();
	int getColIndex();*/
	//CREATE_FUNC(GameLayer);
	void initData();
	PROP_CATEGORY getCateGory();
	void setIsSelected(bool flag);
	bool getIsSelected();

	

	void propUsedUp();
public:
	void setPropNum(int num){ _propNum = num; };
	int getPropNum(){ return _propNum; };
	int getCost(){ return _cost; };
public:
	static const std::string FILE_PATH;
	static const int PROP_NUM;
private:
	Size _winSize;
	bool _isSelected;
	PROP_CATEGORY _propCategory;
	Sprite* _iconBtn;
	Label* _tipLabel;
	int _propNum;
	int _cost;
};

#endif