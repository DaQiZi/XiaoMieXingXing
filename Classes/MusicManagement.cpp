#include "MusicManagement.h"


const std::string MusicManagement::MY_EFFECT_STATUS = "MY_EFFECT_STATUS";
const std::string MusicManagement::MY_MUSIC_STATUS = "MY_MUSIC_STATUS";
const std::string MusicManagement::BGM = "audio/bg_mainmenu.mp3";
const std::string MusicManagement::BTN_EFFECT = "audio/btnPress.mp3";
const std::string MusicManagement::STAR_TOUCH = "audio/starTouch.mp3";
const std::string MusicManagement::STAR_REMOVE = "audio/starRemove.mp3";
const std::string MusicManagement::ENCOUNRAGE_EFFECT = "audio/ef_guli_";
const std::string MusicManagement::PROP_BOOM = "audio/ef_daoju_1_bomb.mp3";
const std::string MusicManagement::PROP_PAINT = "audio/ef_daoju_4_magic.mp3";
const std::string MusicManagement::PROP_STICK = "audio/ef_daoju_2_brush.mp3";
const std::string MusicManagement::PROP_TRANS = "audio/ef_daoju_3_reset.mp3";

const std::string MusicManagement::LEVEL_FAIL = "audio/ef_guanqia_fail.mp3";
const std::string MusicManagement::GAME_START = "audio/ef_guanqia_start.mp3";
const std::string MusicManagement::LEVEL_PASS = "audio/ef_guanqia_pass.mp3";
const std::string MusicManagement::CHALLENGE_SUCCESS = "audio/ef_tiaozhan_succ.mp3";
MusicManagement* MusicManagement::getInstance(){
	static MusicManagement management;
	return &management;
}

void MusicManagement::playMenuBGMusic(){
	//SimpleAudioEngine::getInstance()-
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM.c_str(), true);
	if (!musicStatuc){
		stopMusic();
	}
}
void MusicManagement::playFightBGMisce(){
	if (musicStatuc){
		SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/zhandou_bg.mp3", true);
	}
	
}
void MusicManagement::playBtnPress(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(BTN_EFFECT.c_str());
	}
}
void MusicManagement::playStarPress(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(STAR_TOUCH.c_str());
	}
}

void MusicManagement::playStarRemove(){
	

	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(STAR_REMOVE.c_str());
	}
}

void MusicManagement::playEncourageEffect(int num){
	if (effectStatus){
		std::string effectName = StringUtils::format("%s%d.mp3", ENCOUNRAGE_EFFECT.c_str(), num).c_str();
		SimpleAudioEngine::getInstance()->playEffect(effectName.c_str());
	}
}

void MusicManagement::playPropBoom(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(PROP_BOOM.c_str());
	}
}
void MusicManagement::playPropPaint(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(PROP_PAINT.c_str());
	}
}
void MusicManagement::playPropStick(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(PROP_STICK.c_str());
	}
}
void MusicManagement::playPropTrans(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(PROP_TRANS.c_str());
	}
}
void MusicManagement::playLevelFail(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(LEVEL_FAIL.c_str());
	}
}
void MusicManagement::playLevelPass(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(LEVEL_PASS.c_str());
	}
}
void MusicManagement::playGameStart(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(GAME_START.c_str());
	}
}
void MusicManagement::playChallengeSuccess(){
	if (effectStatus){
		SimpleAudioEngine::getInstance()->playEffect(CHALLENGE_SUCCESS.c_str());
	}
}

void MusicManagement::proloadMusicRes(){
	auto music = SimpleAudioEngine::getInstance();
	music->preloadBackgroundMusic(BGM.c_str());
	music->preloadEffect(BTN_EFFECT.c_str());
	music->preloadEffect(STAR_TOUCH.c_str());
	music->preloadEffect(STAR_REMOVE.c_str());
	for (int i = 1; i <= 9;++i){
		music->preloadEffect(StringUtils::format("%s%d.mp3",ENCOUNRAGE_EFFECT.c_str(),i).c_str());
	}
	music->preloadEffect(PROP_BOOM.c_str());
	music->preloadEffect(PROP_TRANS.c_str());
	music->preloadEffect(PROP_PAINT.c_str());
	music->preloadEffect(PROP_TRANS.c_str());

	music->preloadEffect(LEVEL_FAIL.c_str());
	music->preloadEffect(LEVEL_PASS.c_str());
	music->preloadEffect(CHALLENGE_SUCCESS.c_str());
	music->preloadEffect(GAME_START.c_str());
	//music->preloadBackgroundMusic("audio/zhandou_bg.mp3");
	//music->preloadEffect("audio/btnPress.mp3");
	//music->preloadEffect("audio/baozha.mp3");
}

void MusicManagement::resumeEffect(){
	
	SimpleAudioEngine::getInstance()->resumeAllEffects();
	effectStatus = true;
	UserDefault::getInstance()->setBoolForKey(MY_EFFECT_STATUS.c_str(), effectStatus);
}
void MusicManagement::resumeMusic(){
	musicStatuc = true;
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	UserDefault::getInstance()->setBoolForKey(MY_MUSIC_STATUS.c_str(), musicStatuc);
}

void MusicManagement::stopMusic(){
	musicStatuc = false;
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	UserDefault::getInstance()->setBoolForKey(MY_MUSIC_STATUS.c_str(), musicStatuc);
}
void MusicManagement::stopEffect(){
	effectStatus = false;
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	UserDefault::getInstance()->setBoolForKey(MY_EFFECT_STATUS.c_str(),effectStatus);
}

MusicManagement::MusicManagement(){
	readStatus();
}
MusicManagement::~MusicManagement(){

}
MusicManagement::MusicManagement(const MusicManagement& management){

}
MusicManagement& MusicManagement::operator  = (const MusicManagement& manage){
	return *this;
}

void MusicManagement::readStatus(){
	musicStatuc = UserDefault::getInstance()->getBoolForKey(MY_MUSIC_STATUS.c_str());
	effectStatus = UserDefault::getInstance()->getBoolForKey(MY_EFFECT_STATUS.c_str());
}

bool MusicManagement::getMusicStatus(){
	return musicStatuc;
}
bool MusicManagement::getEffectStatus(){
	return effectStatus;
}

void MusicManagement::setMusicAndEffectVolumn(float v){
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(v);
	SimpleAudioEngine::getInstance()->setEffectsVolume(v);
}