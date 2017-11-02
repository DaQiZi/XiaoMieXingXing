#include"Star.h"
const float Star::STAR_WIDTH  = 48.0f;
const float Star::STAR_HEIGHT = 48.0f;
const int Star::STAR_CATEGORY_NUM = 5;
void Star::initData(){
	_winSize = Director::getInstance()->getVisibleSize();
	_isSelected = false;
}

bool Star::init(STAR_CATEGORY category){
	if (!Sprite::init()){
		return false;
	}
	initData();
	this->initWithSpriteFrameName(this->getImageName(category));
	this->_starCategory = category;
	return true;
}


Star* Star::create(STAR_CATEGORY category){
	Star* star = new Star();
	if (star&&star->init(category)){
		star->autorelease();
		return star;
	}
	CC_SAFE_DELETE(star);
	return star;
}

std::string Star::getImageName(STAR_CATEGORY category){
	std::string filename = "";
	switch (category)
	{
	case Star::STAR_BLUE:
		filename = "star_blue.png";
		break;
	case Star::STAR_GREEN:
		filename = "star_green.png";
		break;
	case Star::STAR_PURPLE:
		filename = "star_purple.png";
		break;
	case Star::STAR_RED:
		filename = "star_red.png";
		break;
	case Star::STAR_YELLOW:
		filename = "star_yellow.png";
		break;
	default:
		break;
	}
	return filename;
}

void Star::setRowAndColumn(int row, int col){
	_row = row;
	_col = col;
}
int Star::getRowIndex(){
	return _row;
}
int Star::getColIndex(){
	return _col;
}

Star::STAR_CATEGORY Star::getCateGory(){
	return _starCategory;
}

void Star::setIsSelected(bool flag){
	this->_isSelected = flag;
}
bool Star::getIsSelected(){
	return _isSelected;
}
void Star::setCateGory(STAR_CATEGORY category){
	_starCategory = category;
}
