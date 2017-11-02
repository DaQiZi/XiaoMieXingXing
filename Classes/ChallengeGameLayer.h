#ifndef _CHALLENGE_GAME_LAYER_H
#define _CHALLENGE_GAME_LAYER_H
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"StarMatrix.h"
#include"Prop.h"
#include"BloodProgress.h"
using namespace ui;
using namespace cocos2d;
class  ChallengeGameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(ChallengeGameLayer);
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
	//��ʱ���Ľ�����
	void updateTimeLoading(float dt);
	void changeTimeLoading(float dt);

	void checkLabelStatus(float);
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
	//int _targetScore;
	//int _currentLevel;
	int _diamondsNum;
	int _highestScore;

	Label* _currentScoreLabel;
	Label* _highestScoreLabel;
	//Label* _targetScoreLabel;
	//Label* _currentLevelLabel;
	Label* _diamondsNumLabel;
	//////////////////////////////////////////
	StarMatrix* matrix;

	bool _isPass;

	//
	BloodProgress* _tipLoading;
};

#endif