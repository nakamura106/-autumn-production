#include "ScoreTime.h"
#include "../DataBank/DataBank.h"

ScoreTime::ScoreTime()
{
	m_score_time = 0;
}

ScoreTime::~ScoreTime()
{
}

void ScoreTime::TransformFlametoTime()
{
	int end_flame = DataBank::Instance()->GetGameEndFlame();
	m_score_time = end_flame / 60;
}
