#ifndef _STAR_MATRIX_H
#define _STAR_MATRIX_H
#include"cocos2d.h"

#include"Star.h"
#include"Prop.h"
//#include"GameLayer.h"
using namespace cocos2d;
class GameLayer;
class ChallengeGameLayer;
class  StarMatrix : public Node{
public:
	static GameLayer* gameLayer;
	static ChallengeGameLayer* challengeGameLayer;
public:
	~StarMatrix();
	virtual bool init();
	void initData();
	CREATE_FUNC(StarMatrix);
	void initStarMatrix();
	Vec2 getPositionByIndex(int, int);
	void starTouchJudge(Vec2 touch, Prop* prop);
	Star* getStarByTouch(Vec2 touch);
	//得到选择的星星
	void getSelectedStar(Star* star);
	//根据星星的位置，得到一个星星的数据
	bool getSelectedArrayAndJudege(Star* star);
	void deleteSelectedStar();
	void adjustStarMatrix();
	//刷新选择数组的状态。
	void freshenStarMatrix();
	////////////////////////////////////////
	//和道具类有关的东西，需要矩阵自己处理
	void starPropBoom(Star* star);
	void starPropStick(Star* star);
	void produceSelectBox(Star* star);
	void removeSelectBox(Ref* data);
	void starPropPaint();
	void starPropTrans();
	//判断是否还有可以消除的
	void starExistRemove();
	//根据星星的个数来计算
	int getScoreByStarNumber(int num);
	//没有可以消除的星星之后，消除剩余的星星
	void removeRemainingStar(float dt);
	//星星的状态保存到本地
	void saveToLocal();
	void loadToLocal();
	void randomProduceStarMatrix();
	//根据消除的数量产生特效。
	void encourageLabel(int num);
	void countRemainingStarNum();
	//
	void challengeModeProduceMatrix();
private:
	int _rowNum;
	int _colNum;
	int _offsetY;
	std::vector<std::vector<Star*>> _starArray;
	std::vector<Star*> _selectStarArray;
	float _moveSpeed;
	Size _winSize;

	Sprite* _selectBG;
	int _remainingCount;
};

#endif