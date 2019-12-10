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
	m_player_hp = 0;
	m_sleep_gauge = 0;
	m_fg = 0;
}

DataBank::~DataBank()
{
}
