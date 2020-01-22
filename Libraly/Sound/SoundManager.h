#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "AudioPlayer.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// �e�V�[�����Ƃ̉��f�ޓo�^
	void RegisterTitleSound();		// �^�C�g��
	void RegisterSelectSound();		// �Z���N�g
	void RegisterGameMainSound();	// �Q�[�����C��
	void RegisterEndSound();		// �Q�[���G���h

	// �炷�֐�
	void SoundBGM();
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundClickSE();

	void ResetSelectFlag();

	// ����֐�
	void ReleaseTitleSound();
	void ReleaseSelectSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	bool m_select_flag;	// selectSE�����[�v�����Ȃ����߂̃t���O

	
	std::string m_bgm;
	std::string m_select_se;
	std::string m_click_se;

	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;

	int i = 0;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

