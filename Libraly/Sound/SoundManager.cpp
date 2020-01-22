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

	m_pAudio->Load(m_bgm, m_bgm_file);

}

void SoundManager::RegisterSelectSound()
{
	m_bgm_file = "Res/Wav/SelectBgm.wav";
	m_se1_file = "Res/Wav/SelectSE.wav";
	m_se2_file = "Res/Wav/ClickSE.wav";
	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_se1, m_se1_file);
	m_pAudio->Load(m_se2, m_se2_file);

}

void SoundManager::RegisterGameMainSound()
{
}

void SoundManager::RegisterEndSound()
{
}

void SoundManager::UpdatePlaySound()
{

	m_pAudio->Play(m_bgm, -1000, true);
	
	// m_pAudio->Play(m_se2, 0, false);
}

void SoundManager::SoundClickSE()
{
	m_pAudio->Play(m_se2, 0, false);
}

void SoundManager::ReleaseTitleSound()
{
	m_pAudio->Release(m_bgm);
}

void SoundManager::ReleaseSelectSound()
{
	m_pAudio->Release(m_bgm);
	// m_pAudio->Release(m_se1);
	// m_pAudio->Release(m_se2);
}

SoundManager::SoundManager()
{
	m_bgm = "NONE";
}

SoundManager::~SoundManager()
{

}

