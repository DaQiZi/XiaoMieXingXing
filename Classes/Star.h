#ifndef _STAR_H
#define _STAR_H
#include"cocos2d.h"
using namespace cocos2d;
class  Star : public Sprite{
public:
	enum STAR_CATEGORY
	{
		STAR_BLUE = 1,
		STAR_GREEN,
		STAR_PURPLE,
		STAR_RED,
		STAR_YELLOW
	};
	virtual bool init(STAR_CATEGORY category);
	static Star* create(STAR_CATEGORY category);
	static std::string getImageName(STAR_CATEGORY category);
	void setRowAndColumn(int row,int col);
	int getRowIndex();
	int getColIndex();
	//CREATE_FUNC(GameLayer);
	void initData();
	STAR_CATEGORY getCateGory();
	void setCateGory(STAR_CATEGORY category);
	void setIsSelected(bool flag);
	bool getIsSelected();
public:
	static const float STAR_WIDTH;
	static const float STAR_HEIGHT;
	static const int STAR_CATEGORY_NUM;
private:
	Size _winSize;
	STAR_CATEGORY _starCategory;
	int _row;
	int _col;
	bool _isSelected;
};

#endif