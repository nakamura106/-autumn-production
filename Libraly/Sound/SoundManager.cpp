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
	m_click_se_file = "Res/Wav/ClickSE.wav";
	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select1_se, m_se1_file);
	m_pAudio->Load(m_click_se, m_click_se_file);
}

void SoundManager::RegisterSelectSound()
{
	m_bgm_file = "Res/Wav/SelectBgm.wav";
	m_se1_file = "Res/Wav/SelectSE.wav";
	m_se2_file = "Res/Wav/SelectSE.wav";
	m_se3_file = "Res/Wav/SelectSE.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select1_se, m_se1_file);
	m_pAudio->Load(m_select2_se, m_se2_file);
	m_pAudio->Load(m_select3_se, m_se3_file);
}

void SoundManager::RegisterGameMainSound()
{
}

void SoundManager::RegisterEndSound()
{
}


void SoundManager::SoundBGM()
{
	m_pAudio->Play(m_bgm, -1500, true);
}

void SoundManager::SoundSelectBGM()
{
	m_pAudio->Play(m_bgm, 0, true);
}

void SoundManager::SoundSelectSE()
{
	if (m_select1_flag == false)
	{
		m_pAudio->Play(m_select1_se, -1000, false);
		m_select1_flag = true;
		m_select2_flag = false;
		m_select3_flag = false;
	}
}

void SoundManager::SoundSelect2SE()
{
	if (m_select2_flag == false)
	{
		m_pAudio->Play(m_select2_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = true;
		m_select3_flag = false;
		m_select2_flag = true;
	}
}

void SoundManager::SoundSelect3SE()
{
	if (m_select3_flag == false)
	{
		m_pAudio->Play(m_select3_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = false;
		m_select3_flag = true;
	}
}

void SoundManager::SoundClickSE()
{
	m_pAudio->Play(m_click_se, 0, false);
}

void SoundManager::ResetSelectFlag()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;
}

void SoundManager::ReleaseTitleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select1_se);
	
}

void SoundManager::ReleaseSelectSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select1_se);
	m_pAudio->Release(m_select2_se);
	m_pAudio->Release(m_select3_se);
}

SoundManager::SoundManager()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;

	m_bgm = "BGM";
	m_select1_se = "SelectSE";
	m_select2_se = "Select2SE";
	m_select3_se = "Select3SE";
	m_click_se = "ClickSE";
}

SoundManager::~SoundManager()
{

}

