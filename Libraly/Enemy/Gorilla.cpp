#include "Gorilla.h"
#include"../Bullet/BananaBullet.h"
#include"../Bullet/MonkeyBullet.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Collision/ShapeType/ShapeRect.h"
#include"../DataBank/SaveData.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla, 3, 850.f)
{
	LoadAIData(M_AIDataFileName);
	SetAIType();
	CompleteChangeState();

	//ゴリラだけ例外。眠り状態のみ異なる
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;

	//手の位置設定
	m_hand_pos.x = m_draw_param.tex_size_x / 2.f - 100.f;
	m_hand_pos.y = m_draw_param.tex_size_y / 2.f;

	m_jump_acceleration = M_JUMP_ACCELERATION_DEFAULT;
	m_jump_speed = 0.f;
	m_end_jump = false;

	m_shot_adjust_default = m_shot_adjust;

	m_draw_param.tex_size_x = m_draw_param.tex_size_y = M_GORILLA_TEX_SIZE;

	m_pos.y += M_POS_Y_ADJUST;

	m_shape_list.push_back(new ShapeCircle(m_pos.x, 347.0f, m_pos.y, 379.0f, 69.0f, 850.0f));//頭
	m_shape_list.push_back(new ShapeRect(m_pos.x, 441.0f, m_pos.y, 668.0f, 138.0f, 307.0f, 850.0f));//腕
	m_shape_list.push_back(new ShapeCircle(m_pos.x, 333.0f, m_pos.y, 503.0f, 69.0f, 850.0f));//胴体
	m_shape_list.push_back(new ShapeRect(m_pos.x, 280.0f, m_pos.y, 696.0f, 104.0f, 235.0f, 850.0f));// 足

	m_tex_space_front = M_TEX_FRONT_SPACE;

	SaveData::GetInstance().SetNewClearTime(ClearTimeType::Gorilla_Flute, 100);
	SaveData::GetInstance().SetCsvFileData();

}

Gorilla::~Gorilla()
{
}

void Gorilla::Init()
{
	
}

EnemyAIType Gorilla::ChangeAIType()
{

	//AI1→初期AI
	//AI2→徘徊
	//AI3→追跡のみ
	//AI4→叩きつけ
	//AI5→バナナ投げ
	//AI6→サル召喚
	//AI7→Wave2～
	//AI8→Wave2～
	//AI9→Wave2～
	//AI10→必殺技

	//元の初期AI
	return EnemyAIType::AI1;

	//必殺技
	if (m_do_deadly_ai == false && m_now_wave == m_max_wave) {

		m_do_deadly_ai = true;

		return EnemyAIType::DeadlyAi;
	}

	EnemyAIType now_ai = GetNowAI();

	//プレイヤーとエネミーの距離
	float p_e_distance = fabsf(m_player_center_pos - m_map_pos);

	if (now_ai == EnemyAIType::AI4 ||
		now_ai == EnemyAIType::AI5 ||
		now_ai == EnemyAIType::AI6) {

		//3種類の攻撃の後は決まった攻撃
		return EnemyAIType::AI3;

	}

	//ゲージステージ(段階)0はゲージ量0を意味する
	if (m_fatigue_gage_stage == EnemyGageStage::Zero && m_sleep_gage_stage == EnemyGageStage::Zero && m_now_wave == 1) {

		return EnemyAIType::AI2;

	}

	//乱数を入手
	int random = RandomTool::GetRandom();

	//追跡のみを行う、Player散策AI
	if (p_e_distance >= 700.f) {

		return EnemyAIType::AI3;

	}
	else {
		//4種類の攻撃をランダムに繰り出す
		switch (random % 4)
		{
		case 0:
			return EnemyAIType::AI4;

		case 1:
			return EnemyAIType::AI5;

		case 2:
			return EnemyAIType::AI6;

		case 3:
			if (m_now_wave == 1) {
				return EnemyAIType::AI2;
			}
			break;
		}
	}

	random = RandomTool::GetRandom();

	//wave2以降限定AI
	switch (random % 3)
	{
	case 0:
		return EnemyAIType::AI7;

	case 1:
		return EnemyAIType::AI8;

	case 2:
		return EnemyAIType::AI9;

	default:
		break;
	}

	return EnemyAIType::AI1;
}

void Gorilla::EnemyAttack1()
{
	//ドラミング
	//ドラミング中はプレイヤー弾を無効化
	m_do_doraming = true;
}

void Gorilla::EnemyAttack2()
{

	//wave2以降のみ、衝撃波
	if (m_now_wave == 1)return;

	//叩きつけ
	if (GetAnimationTexNum() >= M_ATTACK2_ANIM_TEX_NUM && m_do_bullet != true) {

		m_shot_adjust.y = m_draw_param.tex_size_y / 2.f + M_INPACT_B_ADJUST_Y;

		if (m_direction == Direction::LEFT) {
			m_shot_adjust.x = m_draw_param.tex_size_x / 2.f + M_INPACT_LEFT_B_ADJUST;
		}
		else {
			m_shot_adjust.x = m_draw_param.tex_size_x / 2.f + M_INPACT_RIGHT_B_ADJUST;
		}

		CreateBullet(Direction::LEFT, m_speed, 0.f, false, 0, GameCategoryTextureList::GameEnemy_Bullet_Inpact, 2, 2, 3, 0, M_INPACT_ACTIVE_DISTANCE, false, 512);

		CreateBullet(Direction::RIGHT, m_speed, 0.f, false, 0, GameCategoryTextureList::GameEnemy_Bullet_Inpact, 2, 2, 3, 0, M_INPACT_ACTIVE_DISTANCE, false, 512);

		m_shot_adjust = m_shot_adjust_default;

		m_do_bullet = true;

	}
}

void Gorilla::EnemyAttack3()
{
	//バナナ投げ
	if (m_do_bullet != true) {
		CreateBanana();
		m_do_bullet = true;
	}

	//手の位置調整
	int anim_num = GetAnimationTexNum();
	if (anim_num > 0 && anim_num <= m_anim_param.split_all) {

		m_hand_pos.y = M_BANANA_HAND_POS_Y[anim_num - 1];

		if (m_direction == Direction::LEFT) {
			m_hand_pos.x = M_BANANA_HAND_POS_X[anim_num - 1];
		}
		else {
			m_hand_pos.x = m_draw_param.tex_size_x - M_BANANA_HAND_POS_X[anim_num - 1];
		}
	}

}

void Gorilla::EnemyAttack4()
{
	//サル召喚
	if (m_do_bullet != true) {
		CreateMonkey();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyFly()
{
	//ジャンプ
	//既にジャンプし終わっている場合、動作無し

	if (m_end_jump == true) {
		if (m_is_animation_end == true) {
			ChangeState(EnemyStateType::Wait);
		}

		return;
	}

	int anim_tex_num = GetAnimationTexNum();

	if (m_is_flying == true) {
		//ジャンプ中
		EnemyBase::EnemyMove();

		m_pos.y -= m_jump_speed;

		m_jump_speed -= m_jump_acceleration;

		//1/21雑コード
		if (m_anim_param.split_all >= 16) {
			if (anim_tex_num > 10) {
				m_anim_param.split_all = 13;
			
			}
		}
		else {
			if (m_is_animation_end == true) {
				m_draw_param.tu = m_draw_param.tv = 3.f;
			}
		}

		if (m_pos.y >= M_INIT_POS_Y - m_draw_param.tex_size_y / 2.f + M_POS_Y_ADJUST) {

			m_pos.y = M_INIT_POS_Y - m_draw_param.tex_size_y / 2.f + M_POS_Y_ADJUST;

			//m_animation_stop = false;

			m_is_flying = false;

			m_end_jump = true;

			//1/21雑コード
			m_draw_param.tu = 1.f;
			m_draw_param.tv = 4.f;
			m_anim_param.split_all = 16;

		}

	}
	else {
		if (anim_tex_num >= M_JUMP_STOP_ANIM_FLAME) {

			m_is_flying = true;

			//m_animation_stop = true;
		}
	}

}

void Gorilla::EnemyDead()
{
	EnemyBase::EnemyDead();

	if (m_is_animation_end == true) {
		m_draw_param.tu = 4.f;
		m_draw_param.tv = 4.f;
	}
}

void Gorilla::InitAllState()
{
	EnemyBase::InitAllState();

	m_do_doraming = false;

	m_anim_param.change_flame = M_ANIM_FLAME;

}

void Gorilla::InitSleepState()
{
	//眠りモーションは画像使用枚数が異なる
	m_anim_param.split_all = 8;
}

void Gorilla::InitFlyState()
{

	EnemyBase::InitFlyState();

	m_jump_speed = M_JUMP_SPEED_DEFAULT;
	m_end_jump = false;

	m_anim_param.change_flame = 5;
}

void Gorilla::CreateBanana()
{
	Position b_pos = GetShotPos(static_cast<Direction>(m_direction));

	bullet_list.push_back(
		new BananaBullet(
			b_pos.x,
			b_pos.y,
			m_speed,//x速度
			-m_speed,//y速度
			0.25f,//加速度
			(Direction)m_direction,
			this,
			M_FRAME_BANANA_START//動き始めるアニメーション番号
		)
	);
}

void Gorilla::CreateMonkey()
{
	float pos_x = 0.f;

	Direction move_direction = Direction::LEFT;

	if (m_direction == Direction::LEFT) {
		pos_x = -300.f;
		move_direction = Direction::RIGHT;
	}
	else {
		pos_x = 3600.f;//マップ右端
		move_direction = Direction::LEFT;
	}

	bullet_list.push_back(
		new MonkeyBullet(
			pos_x,
			m_pos.y + m_draw_param.tex_size_y / 2.f,
			m_speed/2.f,//x速度
			move_direction,
			-m_speed,//y速度
			0.15f//加速度
		)
	);

}
