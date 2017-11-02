#ifndef _GAME_LAYER_H
#define _GAME_LAYER_H
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"StarMatrix.h"
#include"Prop.h"
using namespace ui;
using namespace cocos2d;
class  GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void initData();
	void initBG();
	void pauseMenu();
	void trasitionLabel();
	void produStarMatrixAndAddListener();
	//////////////////////////////////////////
	//�͵����йصķ�����
	void propTouchJudge(Vec2 touch);
	void propUseComplate(Ref* data);

	///////////////////////////////////////////
	//���·���
	void updateTargetScore(int score);

	void gameComplate();
	//void gameFail();
	//���浽�����ļ���
	void saveToLocal();

	//���״̬
	void checkLabelStatus(float );
private:
	Size _winSize;
	Button* pauseBtn;
	///////////////////////////////////////////
	//�͵����йصġ�
	Vector<Prop*> _propVector;
	Prop* _selectProp;
	///////////////////////////////////////////
	//�����ϵ�һЩС��ǩ
	int _currentScore;
	int _targetScore;
	int _currentLevel;
	int _diamondsNum;


	Label* _currentScoreLabel;
	Label* _targetScoreLabel;
	Label* _currentLevelLabel;
	Label* _diamondsNumLabel;
	//////////////////////////////////////////
	StarMatrix* matrix;

	bool _isPass;
};

#endif