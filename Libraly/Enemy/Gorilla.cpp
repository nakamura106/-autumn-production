#include "Gorilla.h"
#include"../Bullet/BananaBullet.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla)
{
	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	//�S����������O�B�����Ԃ݈̂قȂ�
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;

	//��̈ʒu�ݒ�
	m_hand_pos.x = m_draw_param.tex_size_x / 2.f - 100.f;
	m_hand_pos.y = m_draw_param.tex_size_y / 2.f;
}

Gorilla::~Gorilla()
{
}

void Gorilla::Init()
{
	
}

EnemyAIType Gorilla::ChangeAIType()
{
	return EnemyAIType::AI1;
}

void Gorilla::EnemyAttack1()
{
	//�h���~���O
}

void Gorilla::EnemyAttack2()
{
	//�@����
}

void Gorilla::EnemyAttack3()
{
	//�o�i�i����
	if (m_do_bullet != true) {
		CreateBanana();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyFly()
{
	//�W�����v
}

void Gorilla::CreateBanana()
{
	Position b_pos = GetShotPos();

	bullet_list.push_back(
		new BananaBullet(
			b_pos.x,
			b_pos.y,
			m_speed,//x���x
			-m_speed,//y���x
			0.25f,//�����x
			(Direction)m_direction,
			this,
			12//�����n�߂�A�j���[�V�����ԍ�
		)
	);
}
