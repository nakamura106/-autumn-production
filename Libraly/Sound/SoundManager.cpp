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
	m_se1_file = "Res/Wav/SelectSE.wav";
	m_se2_file = "Res/Wav/ClickSE.wav";
	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select_se, m_se1_file);
	m_pAudio->Load(m_click_se, m_se2_file);
}

void SoundManager::RegisterSelectSound()
{
	m_bgm_file = "Res/Wav/SelectBgm.wav";
	m_se1_file = "Res/Wav/SelectSE.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select_se, m_se1_file);
}

void SoundManager::RegisterGameMainSound()
{
}

void SoundManager::RegisterEndSound()
{
}

void SoundManager::SoundBGM()
{
	m_pAudio->Play(m_bgm, -500, true);
}

void SoundManager::SoundSelectBGM()
{
	m_pAudio->Play(m_bgm, -500, true);
}

void SoundManager::SoundSelectSE()
{
	if (m_select_flag == false)
	{
		m_pAudio->Play(m_select_se, 0, false);
		m_select_flag = true;
	}
}

void SoundManager::SoundClickSE()
{
	m_pAudio->Play(m_click_se, 0, false);
}

void SoundManager::ResetSelectFlag()
{
	m_select_flag = false;
}

void SoundManager::ReleaseTitleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select_se);
	
}

void SoundManager::ReleaseSelectSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select_se);
}

SoundManager::SoundManager()
{
	m_select_flag = false;
	m_bgm = "BGM";
	m_select_se = "SelectSE";
}

SoundManager::~SoundManager()
{

}

