#include "SoundManager.h"

SoundManager* SoundManager::p_instance = 0;

SoundManager* SoundManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new SoundManager;
	}

	return p_instance;
}

void SoundManager::RegisterTitleSound()
{
	m_bgm_file = "Res/Wav/TitleBgm.wav";
	AudioPlayer::GetInstance()->Load(m_bgm, m_bgm_file);
}

void SoundManager::RegisterSelectSound()
{
}

void SoundManager::RegisterGameMainSound()
{
}

void SoundManager::RegisterEndSound()
{
}

void SoundManager::UpdatePlaySound()
{
	AudioPlayer::GetInstance()->Play(m_bgm, 0, true);

}

void SoundManager::ReleaseTitleSound()
{
	AudioPlayer::GetInstance()->Release(m_bgm);
}

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

