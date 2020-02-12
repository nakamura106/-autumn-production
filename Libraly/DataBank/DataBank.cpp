#include "DataBank.h"

DataBank* DataBank::p_instance = 0;

DataBank* DataBank::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new DataBank();
	}
	
	return p_instance;
}

DataBank::DataBank()
{
	m_fatigue_gauge = 0;
	m_map_pos = 0;
	m_player_hp = 5;
	m_sleep_gauge = 0;
	m_fg = 0;
	note1 = 0;
	note2 = 0;
	note3 = 0;
	m_bullet_type = 0;
	m_floor1 = 0.0f;
	m_is_game_clear = false;
	m_is_game_over = false;
	m_Pdirection=(int)Direction::RIGHT;
	m_centerpos.x = 0;
	m_centerpos.y = 0;
	m_bullet_death_pos.x = 0.f;
	m_bullet_death_pos.y = 0.f;

	for (int i = 0; i < (int)P_effect::MaxEffect; i++)
	{
		m_PlayerEffect[i] = false;
	}
	for (int i = 0; i<(int)WaveType::WaveMax; i++)
	{
		m_wave_change[i] = false;
	}
	m_PlayerType = (int)Player::PlayerTypeTrumpet;
	m_wave_state = WaveState::None;
	
	m_do_enemy_deadly_ai = false;

}



DataBank::~DataBank()
{

}

void DataBank::ResetData()
{
	m_fatigue_gauge = 0;
	m_sleep_gauge = 0;
}

void DataBank::SetPlayerEffect(P_effect effect_)
{
	switch (effect_)
	{
	case P_effect::None:
		m_PlayerEffect[0] = true;
		break;
	case P_effect::Debuff:
		m_PlayerEffect[1] = true;
		break;
	case P_effect::Failure:
		m_PlayerEffect[2] = true;
		break;
	case P_effect::Hit:
		m_PlayerEffect[3] = true;
		break;
	case P_effect::Landing:
		m_PlayerEffect[4] = true;
		break;
	case P_effect::Shot:
		m_PlayerEffect[5] = true;
		break;
	case P_effect::Sweat:
		m_PlayerEffect[6] = true;
		break;
	default:
		break;
	}
}

int DataBank::GetPlayerEffect(P_effect p_effect_)
{
	switch (p_effect_)
	{
	case P_effect::Debuff:
		return m_PlayerEffect[(int)P_effect::Debuff];
		break;
	case P_effect::Failure:
		return m_PlayerEffect[(int)P_effect::Failure];
		break;
	case P_effect::Hit:
		return m_PlayerEffect[(int)P_effect::Landing];
		break;
	case P_effect::Landing:
		return m_PlayerEffect[(int)P_effect::Shot];
		break;
	case P_effect::Shot:
		return m_PlayerEffect[(int)P_effect::Sweat];
		break;
	default:
		break;
	}

	return 0;

}
