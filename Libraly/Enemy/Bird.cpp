#include"Bird.h"

Bird::Bird()
	:EnemyBase(0.f, EnemyID::Seagull)
{



}

Bird::~Bird()
{
}

void Bird::Init()
{
}

void Bird::SetRectangle()
{
	m_rect_param.shift_x	= 250.f;//105.0f;
	m_rect_param.shift_y	= 440.0f;
	m_rect_param.width		= 829.0f;
	m_rect_param.height		= 561.0f;
}

EnemyAIType Bird::ChangeAIType()
{
	return EnemyAIType::AI1;
}

void Bird::EnemyAttack1()
{

}

void Bird::EnemyAttack2()
{

}

void Bird::EnemyAttack3()
{

}
