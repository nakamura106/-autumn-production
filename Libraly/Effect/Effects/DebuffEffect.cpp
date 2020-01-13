#include "DebuffEffect.h"

DebuffEffect::DebuffEffect()
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	m_id = EffectID::DebuffEffect;

	// キャラの座標をどうやってX,Yに代入するのか？
	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	// オフセットは後で確認後に正しい値に修正
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameDebuffEfect;
}

void DebuffEffect::Update()
{
}

void DebuffEffect::Draw()
{
}
