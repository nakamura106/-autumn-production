#include"Bird.h"
#include"../Bullet/ShitBullet.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Collision/ShapeType/ShapeRect.h"

Bird::Bird()
	:EnemyBase(0.f, EnemyID::Seagull, 2, 512.f)
{

	LoadAIData(M_AIDataFileName);

	//使用するAI番号の設定
	SetAIType();

	CompleteChangeState();

	m_savetime_shit_cycle = FlameTimer::GetNowFlame();
	m_is_init_motion_end = false;
	m_shot_adjust.x = m_draw_param.tex_size_x / 2.f;
	m_shot_adjust.y = m_draw_param.tex_size_y - 200.f;

	m_speed_y_default = m_speed;
	--m_anim_param.change_flame;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 137.0f, m_pos.y, 322.0f, 151.0f, 32.0f, 512.0f));//頭
	m_shape_list.push_back(new ShapeRect(m_pos.x, 285.0f, m_pos.y, 338.0f, 142.0f, 84.0f, 512.0f));//胴体
	m_shape_list.push_back(new ShapeCircle(m_pos.x, 365.0f, m_pos.y, 299.0f, 47.0f, 512.0f));//羽
}

Bird::~Bird()
{

}

void Bird::Init()
{
	
}

void Bird::SetRectangle()
{//140,397,
	m_rect_param.shift_x	= 250.f;//105.0f;
	m_rect_param.shift_y	= 440.0f;
	m_rect_param.width		= 829.0f;
	m_rect_param.height		= 561.0f;
}

EnemyAIType Bird::ChangeAIType()
{
	//AI1→初期AI
	//AI2→飛んで徘徊後、降りてくる

	//AI3→飛んでそのまま飛行
	//AI4→降りてきて休息

	//AI5→飛んでいる前提でハネ発射
	//AI6→飛んでいる前提でフン発射

	//AI7以降はWave2?

	//AI10は必殺技枠(昇り・降り込み)

	EnemyAIType now_ai = GetNowAI();

	//必殺技
	if (m_fatigue_gage_stage >= EnemyGageStage::Half_Up &&
		now_ai != EnemyAIType::AI3 && 
		now_ai != EnemyAIType::AI5 && 
		now_ai != EnemyAIType::AI6 && 
		m_do_deadly_ai == false)
	{
		m_do_deadly_ai = true;

		return EnemyAIType::DeadlyAi;
	}

	//プレイヤーとエネミーの距離
	float p_e_distance = fabsf(m_player_center_pos - m_map_pos);

	//乱数を入手
	int random = RandomTool::GetRandom();

	if (now_ai == EnemyAIType::AI5 ||
		now_ai == EnemyAIType::AI6) {

		//空中攻撃後は降りてきて休息
		return EnemyAIType::AI4;

	}

	//ゲージステージ(段階)0はゲージ量0を意味する
	if (m_fatigue_gage_stage == EnemyGageStage::Zero && m_sleep_gage_stage == EnemyGageStage::Zero && now_ai != EnemyAIType::AI3) {

		return EnemyAIType::AI2;

	}

	//追跡のみを行う、Player散策AI
	if (now_ai==EnemyAIType::AI3) {

		//2種類の攻撃をランダムに繰り出す
		switch (random % 2)
		{
		case 0:
			return EnemyAIType::AI5;

		case 1:
			return EnemyAIType::AI6;

		}

	}
	else {

		//飛んで飛行状態に
		return EnemyAIType::AI3;
	}

	return EnemyAIType::AI1;
}

void Bird::InitFlyState()
{
	if (m_is_flying == true) {
		InitAttack1State();
	}
	else {
		InitFlappingState();
	}
}

void Bird::InitAttack1State()
{
	EnemyBase::InitAttack1State();

	//この画像のみ分割数が異なる
	m_anim_param.split_all		= 24;
	m_anim_param.split_height	= 4;
	m_anim_param.split_width	= 8;
}

void Bird::InitFlappingState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_FlappingLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_FlappingRight;
	}
}

void Bird::EnemyAttack1()
{

}

void Bird::EnemyAttack2()
{
	//ハネ攻撃
	if (GetAnimationTexNum() > M_ATTACK2_ANIM_TEX_NUM && !m_do_bullet) {

		m_do_bullet = true;

		int feather_num = M_SHOT_FEATHER_NUM;

		if (GetNowAI() == EnemyAIType::DeadlyAi) {
			feather_num = M_DEADLY_FEATHER_NUM;
		}

		for (int i = 0;i < feather_num;++i) {
			//弾発射
			CreateBullet(
				static_cast<Direction>(m_direction),
				m_speed - (static_cast<float>(i) - (static_cast<float>(feather_num + 1) / 2.f)),
				m_speed + (static_cast<float>(i) - (static_cast<float>(feather_num + 1) / 2.f)),
				true,
				45,
				GameEnemy_Bullet_Normal,
				1,
				2,
				1,
				1
			);

		}

	}

}

void Bird::EnemyAttack3()
{

	EnemyMove();

	if (FlameTimer::GetNowFlame(m_savetime_shit_cycle) >= M_SHIT_CYCLE) {
		//発射
		CreateShitBullet();

		m_savetime_shit_cycle = FlameTimer::GetNowFlame();

	}
}

void Bird::EnemyFly()
{
	//飛行状態
	if (m_is_flying == true) {
		FlyStateFall();
	}
	else {
		FlyStateRise();
	}
}

void Bird::EnemyMove()
{
	EnemyBase::EnemyMove();

	FlyDeceleration(1.8f);
}

void Bird::EnemyWait()
{
	EnemyBase::EnemyWait();

	if (m_is_flying == true) {
		FlyDeceleration(1.8f);
	}
}

void Bird::FlyStateRise()
{
	//モーション切り替え処理
	if (m_is_init_motion_end != true) {

		if (m_is_animation_end == true) {
			//最初のモーションのアニメーションが終わり次第、
			//待機モーションへ
			EnemyBase::InitFlyState();

			//移動開始
			m_is_init_motion_end = true;
		}
		else {
			return;
		}

	}

	if (GetAnimationTexNum() >= 2) {
		//上空に飛んでいく
		m_pos.y -= m_speed_y_default;

		m_speed_y_default -= M_FLY_DECELERASION;

	}
	else {
		m_speed_y_default = m_speed;
	}

	//上空まで飛んだ
	if (m_pos.y <= M_SKY_HEIGHT) {

		m_pos.y = M_SKY_HEIGHT;

		m_is_flying = true;

		ChangeState(EnemyStateType::Wait);

	}
}

void Bird::FlyStateFall()
{

	//最後のモーションに行き次第、状態遷移
	if (m_is_animation_end == true) {

		m_is_flying = false;

		ChangeState(EnemyStateType::Wait);

	}

	//指定されたモーションの場合は動作しない
	if (GetAnimationTexNum() < M_FLYFALL_STOP_ANIMATION) {
		//停止
		return;
	}

	//移動処理等
	if (m_pos.y >= M_INIT_POS_Y - m_draw_param.tex_size_y / 2.f) {

		m_pos.y = M_INIT_POS_Y - m_draw_param.tex_size_y / 2.f;

		m_animation_stop = false;

	}
	else {
		//地上に斜め方向で降りてくる
		m_pos.y += m_speed;

		EnemyBase::EnemyMove();

		//落下中はアニメーションストップ
		m_animation_stop = true;
	}

	
	
}

void Bird::InitAttack3State()
{
	InitWalkState();
}

void Bird::CreateShitBullet()
{
	Position b_pos = GetShotPos(static_cast<Direction>(m_direction));

	bullet_list.push_back(
		new ShitBullet(
			b_pos.x,
			b_pos.y,
			0.f,
			m_speed,
			0.05f,		//加速度
			(Direction)m_direction
		)
	);

}

void Bird::InitAllState()
{
	EnemyBase::InitAllState();

	//現在のフレームを取得
	m_savetime_shit_cycle = FlameTimer::GetNowFlame();

	m_is_init_motion_end = false;

	//基本この分割数
	m_anim_param.split_all = 12;
	m_anim_param.split_height =
	m_anim_param.split_width = 4;

}

void Bird::FlyDeceleration(float default_speed_)
{
	if (GetAnimationTexNum() >= 2) {
		m_pos.y -= m_speed_y_default;

		m_speed_y_default -= M_FLY_DECELERASION;
	}
	else {
		m_speed_y_default = default_speed_;
	}
}

