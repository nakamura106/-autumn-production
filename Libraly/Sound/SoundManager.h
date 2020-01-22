#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "AudioPlayer.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// 各シーンごとの音素材登録
	void RegisterTitleSound();

	void RegisterSelectSound();

	void RegisterGameMainSound();

	void RegisterEndSound();

	// 各シーンのSoundUpdate;
	void UpdatePlaySound();

	void SoundClickSE();

	void ReleaseTitleSound();

	void ReleaseSelectSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	std::string m_bgm;
	std::string m_se1;
	std::string m_se2;
	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;

	int i = 0;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

