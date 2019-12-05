#include "Mouse.h"
#include "../Player/TrpPlayer.h"

//定数値は仮決め

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Refuge_Time	100				//逃げ回る時間
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

#define Fatigue_Gauge_Max 100		//疲労ゲージ上限
#define Sleep_Gauge_Max	100			//睡眠ゲージ上限

#define Attack_Interval 100			//攻撃感覚
#define HedgeHog_Speed 10			//読んで字の如く

TrpPlayer* trpplayer;

HedgeHog::HedgeHog()
{
	m_enemy_id = EnemyID::BossTypeMax;
	m_attack_repertory = AttackRepertoryofHedgeHog::None;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = NULL;
	m_sleep_gauge = NULL;
	m_time_of_break = 0;
	m_refuge_time = Refuge_Time;
	m_is_break = false;
	m_is_delete = true;
	m_is_hit_judge = false;
	m_is_speed_up = false;
	//m_speed = 5.0f;
	m_do_needle = false;
}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{
	/*11/26 注!!仮実装のコード*/
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DashAttackLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DashAttackRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_NeedleAttackLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_NeedleAttackRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_FlyNeedle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Needle);

}

void HedgeHog::InitAttackRepertory()
{
	switch (m_attack_repertory)
	{
		//トゲ発射
	case (int)AttackRepertoryHedgeHog::NeedleFire:
		if (m_direction == Direction::LEFT) {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackLeft;
		}
		else {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackRight;
		}
		break;

	default:
		if (m_direction == Direction::LEFT) {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackLeft;
		}
		else {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackRight;
		}
		break;
	}
}

void HedgeHog::EnemyAttack()		//エネミー攻撃
{
	/*
		敵からプレイヤーへの状態に応じて攻撃種を変更
	*/

	switch (m_attack_repertory)
	{
	case (int)AttackRepertoryHedgeHog::Rush:
		Rush();
		break;

	case (int)AttackRepertoryHedgeHog::HeadButt:
		Headbutt();
		break;

	case (int)AttackRepertoryHedgeHog::NeedleFire:
		ShotNeedle();
		break;

	default:
		/*
			!!
		*/
		break;
	}

}

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	if (FlameTimer::GetNowFlame(m_state_saveflame) > 120 && m_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	if (FlameTimer::GetNowFlame(m_state_saveflame) > 60 && m_animation_end) {
		m_attack_repertory = (int)AttackRepertoryHedgeHog::NeedleFire;
		return EnemyStateType::Attack;
	}

	return EnemyStateType::Walk;
}

EnemyStateType HedgeHog::ChangeStateFromRefuge()
{
	return EnemyStateType::Refuge;
}

EnemyStateType HedgeHog::ChangeStateFromAttack()
{
	if (m_animation_end) {
		m_do_needle = false;
		return EnemyStateType::Wait;
	}

	return EnemyStateType::Attack;
}

EnemyStateType HedgeHog::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
}


//	ハリネズミAttackの処理（仮）

void HedgeHog::Headbutt()
{
	/*
		頭突き処理
		プレイヤー方向に頭突き
		ｘ方向へ素早く移動して元の座標まで戻る
		頭突き距離　150
	*/

	//	アニメーション変更

}

void HedgeHog::Rush()
{
	/*
		突進処理
		一定加速後同じ速度で減速
	*/

	//	アニメーション変更

}

void HedgeHog::ShotNeedle()
{
	/*
		とげ発射処理
		とげ発射方向　－＞　プレイヤーの座標
		追尾　なし
		発射　3way 2回くらい？
	*/
	if (GetAnimationTexNum() > 7 && !m_do_needle) {
		//発射したかどうかのフラグをON
		m_do_needle = true;

		//弾発射
		CreateNeedle();

	}

}

void HedgeHog::CreateNeedle()
{
	Position b_pos;

	//発射位置調整
	b_pos.y = m_pos.y + M_NEEDLE_ADJUST_Y;

	if (m_direction == Direction::LEFT) {
		b_pos.x = m_pos.x + M_NEEDLE_ADJUST_X;
	}
	else {
		b_pos.x = m_pos.x - M_NEEDLE_ADJUST_X + m_draw_param.tex_size_x;
	}

	//Bullet(ハリ)生成
	bullet_list.push_back(new EnemyBullet(b_pos.x, b_pos.y, 5.f, (Direction)m_direction));

}

