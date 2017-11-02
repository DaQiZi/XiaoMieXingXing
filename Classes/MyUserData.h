#ifndef __MY_USER_DATA_
#define __MY_USER_DATA_
#include"cocos2d.h"
#include"Config.h"
using namespace cocos2d;
class MyUserData
{
public:

	static MyUserData* getInstance();
	void addDiamonds(int num){ _diamonds += num; };
	void setDiamonds(int num){ _diamonds = num; };
	int getDiamonds(){ return _diamonds; };

	int getCurrentScore(){ return _currentscore; };
	int getTargetScore();
	int getCurrentLevel(){ return _currentLevel; };

	void setCurrentLevel(int level){ _currentLevel = level; };
	void setCurrentScore(int score){ _currentscore = score; };




	int getPropBoomNum(){ return _propBoomNum; };
	int getPropPaintNum(){ return _propPaintNum; };
	int getPropStickNum(){ return _propStickNum; };
	int getPropTransNum(){ return _propTransNum; };

	void  setPropBoomNum(int num){ _propBoomNum = num; };
	void  setPropPaintNum(int num){ _propPaintNum = num; };
	void  setPropStickNum(int num){ _propStickNum = num; };
	void  setPropTransNum(int num){ _propTransNum = num; };

	bool getIsContinue(){ return _isContinue; };
	void setIsCoutinue(bool flag){ _isContinue = flag; };

	bool getIsFirstCome(){ return _isFirstCome; };
	void setIsFirstCome(bool flag){ _isFirstCome = flag; };

	bool getIsChallenge(){ return _isChallenge; };
	void setISChallenge(bool flag){ _isChallenge = flag; };

	int getHighestScore(){ return _highestScore; };
	void setHighestScore(int num){ _highestScore = num; };

	void saveData();
private:
	MyUserData();
	~MyUserData();
	MyUserData(const MyUserData& data);
	MyUserData operator=(const MyUserData& data);
	//static MyUserData* _myuserData;
	int _diamonds;
	int _currentscore;
	int _targetScore;
	int _currentLevel;
	int _highestScore;
	////////////////////
	//和道具有关的数据成员
	int _propBoomNum;
	int _propPaintNum;
	int _propStickNum;
	int _propTransNum;

	bool _isContinue;
	bool _isFirstCome;

	bool _isChallenge;

private:
	static const std::string IS_CONTINUE;
	static const std::string CURRETN_SOCRE;
	static const std::string CURRENT_LEVEL;
	static const std::string STAR_DIAMONDS;
	static const std::string HIGHEST_SCORE;

	static const std::string PROP_BOOM_NUM;
	static const std::string PROP_PAINT_NUM;
	static const std::string PROP_TRANS_NUM;
	static const std::string PROP_STICK_NUM;
};


#endif