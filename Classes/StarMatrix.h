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
	//�õ�ѡ�������
	void getSelectedStar(Star* star);
	//�������ǵ�λ�ã��õ�һ�����ǵ�����
	bool getSelectedArrayAndJudege(Star* star);
	void deleteSelectedStar();
	void adjustStarMatrix();
	//ˢ��ѡ�������״̬��
	void freshenStarMatrix();
	////////////////////////////////////////
	//�͵������йصĶ�������Ҫ�����Լ�����
	void starPropBoom(Star* star);
	void starPropStick(Star* star);
	void produceSelectBox(Star* star);
	void removeSelectBox(Ref* data);
	void starPropPaint();
	void starPropTrans();
	//�ж��Ƿ��п���������
	void starExistRemove();
	//�������ǵĸ���������
	int getScoreByStarNumber(int num);
	//û�п�������������֮������ʣ�������
	void removeRemainingStar(float dt);
	//���ǵ�״̬���浽����
	void saveToLocal();
	void loadToLocal();
	void randomProduceStarMatrix();
	//��������������������Ч��
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