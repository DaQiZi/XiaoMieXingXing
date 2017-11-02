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
	//和道具有关的方法。
	void propTouchJudge(Vec2 touch);
	void propUseComplate(Ref* data);

	///////////////////////////////////////////
	//更新分数
	void updateTargetScore(int score);

	void gameComplate();
	//void gameFail();
	//保存到本地文件。
	void saveToLocal();
	//定时器的进度条
	void updateTimeLoading(float dt);
	void changeTimeLoading(float dt);

	void checkLabelStatus(float);
private:
	Size _winSize;
	Button* pauseBtn;
	///////////////////////////////////////////
	//和道具有关的。
	Vector<Prop*> _propVector;
	Prop* _selectProp;
	///////////////////////////////////////////
	//界面上的一些小标签
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