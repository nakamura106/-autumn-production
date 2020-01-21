#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "AudioPlayer.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// �e�V�[�����Ƃ̉��f�ޓo�^
	void RegisterTitleSound();

	void RegisterSelectSound();

	void RegisterGameMainSound();

	void RegisterEndSound();

	// �e�V�[����SoundUpdate;
	void UpdatePlaySound();

	void ReleaseTitleSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	std::string m_bgm;
	std::string m_bgm_file;


};

#endif

