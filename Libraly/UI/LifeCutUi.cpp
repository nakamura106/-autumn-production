#include "../UI/LifeCutUi.h"
#include "../DataBank/DataBank.h"

LifeCutUi::LifeCutUi()
{
	Init();
}

LifeCutUi::~LifeCutUi()
{
}

void LifeCutUi::Init()
{
	m_pos.x = LIFE_CUT_POSX;
	m_pos.y = LIFE_CUT_POSY;

	m_param.texture_id = GameCategoryTextureList::GameLifeBarCut1;
}

void LifeCutUi::Update()
{
	if (DataBank::Instance()->GetFatigueGauge() >= 75.0f)
	{
		m_param.texture_id = GameCategoryTextureList::GameLifeBarCut2;
	}
	else
	{
		m_param.texture_id = GameCategoryTextureList::GameLifeBarCut1;
	}
}
