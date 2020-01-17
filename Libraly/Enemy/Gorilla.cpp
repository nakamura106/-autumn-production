#include "Gorilla.h"
#include"../Bullet/BananaBullet.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla)
{
	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	//ゴリラだけ例外。眠り状態のみ異なる
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;

	//手の位置設定
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
	//ドラミング
}

void Gorilla::EnemyAttack2()
{
	//叩きつけ
}

void Gorilla::EnemyAttack3()
{
	//バナナ投げ
	if (m_do_bullet != true) {
		CreateBanana();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyFly()
{
	//ジャンプ
}

void Gorilla::CreateBanana()
{
	Position b_pos = GetShotPos();

	bullet_list.push_back(
		new BananaBullet(
			b_pos.x,
			b_pos.y,
			m_speed,//x速度
			-m_speed,//y速度
			0.25f,//加速度
			(Direction)m_direction,
			this,
			12//動き始めるアニメーション番号
		)
	);
}
