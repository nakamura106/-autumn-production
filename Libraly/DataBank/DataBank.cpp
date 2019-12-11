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
	note1 = 0;
	note2 = 0;
	note3 = 0;
	m_floor1 = 0.0f;


}

DataBank::~DataBank()
{
}
