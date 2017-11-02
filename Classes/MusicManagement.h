#ifndef _MUSIC_MANAGEMENT_H_
#define _MUSIC_MANAGEMENT_H_
//#include "iostream"
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Config.h"
using namespace cocos2d;
using namespace CocosDenshion;
//using namespace std;
class MusicManagement{
public:
	static MusicManagement* getInstance();
	void playMenuBGMusic();
	void playFightBGMisce();


	void playBtnPress();
	void playStarPress();
	void playStarRemove();
	void playEncourageEffect(int num);
	void playPropBoom();
	void playPropPaint();
	void playPropStick();
	void playPropTrans();
	void playLevelFail();
	void playLevelPass();
	void playGameStart();
	void playChallengeSuccess();

	void proloadMusicRes();
	void stopMusic();
	void stopEffect();
	void resumeEffect();
	void resumeMusic();
	void readStatus();
	bool getMusicStatus();
	bool getEffectStatus();
	void setMusicAndEffectVolumn(float v);
private:
	MusicManagement();
	~MusicManagement();
	MusicManagement(const MusicManagement& management);
	MusicManagement& operator  = (const MusicManagement& manage);
	bool effectStatus = true;
	bool musicStatuc = true;
private:
	static const std::string MY_EFFECT_STATUS;
	static const std::string MY_MUSIC_STATUS;
	static const std::string BGM;
	static const std::string BTN_EFFECT;
	static const std::string STAR_TOUCH;
	static const std::string STAR_REMOVE;
	static const std::string ENCOUNRAGE_EFFECT;

	static const std::string PROP_BOOM;
	static const std::string PROP_PAINT;
	static const std::string PROP_STICK;
	static const std::string PROP_TRANS;

	static const std::string LEVEL_FAIL;
	static const std::string GAME_START;
	static const std::string LEVEL_PASS;
	static const std::string CHALLENGE_SUCCESS;
};



#endif