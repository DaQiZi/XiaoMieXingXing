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

	//检查状态
	void checkLabelStatus(float );
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