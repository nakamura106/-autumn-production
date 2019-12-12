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
	:EnemyBase(2.f,	EnemyID::Hedgehog)
{
	m_is_speed_up = false;
	m_do_needle = false;
	SetRectangle();

	LoadAIData(M_AIDataFileName);
	
}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{
	/*11/26 注!!仮実装のコード*/
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
	//LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
	//LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Left);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Right);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Left);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Right);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_FlyNeedle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Needle);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_HeadAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Left);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_HeadAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Right);

}


void HedgeHog::SetRectangle()
{
	m_rect_param.shift_x = 250.f;//105.0f;
	m_rect_param.shift_y = 440.0f;
	m_rect_param.width = 829.0f;
	m_rect_param.height = 561.0f;
}

void HedgeHog::EnemyAttack1()		//エネミー攻撃
{
	/*
		突進処理
		一定加速後同じ速度で減速
	*/

	if (GetAnimationTexNum() > 9) {
		m_speed /= M_DASHATTACK_SPEED_CHANGE_NUM;
	}
	else {
		m_speed *= M_DASHATTACK_SPEED_CHANGE_NUM;
	}

	EnemyBase::EnemyMove();

}

void HedgeHog::EnemyAttack2()
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

void HedgeHog::EnemyAttack3()
{
	int num = GetAnimationTexNum();

	if (num == 9) {
		EnemyMove();
	}
}

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	if (GetStateSaveFlame() > 120 && m_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	if (GetStateSaveFlame() > 60 && m_animation_end) {
		return EnemyStateType::Attack1;
	}

	return EnemyStateType::Walk;
}

EnemyStateType HedgeHog::ChangeStateFromRefuge()
{
	return EnemyStateType::Refuge;
}

EnemyStateType HedgeHog::ChangeStateFromAttack1()
{
	if (m_animation_end) {
		m_do_needle = false;
		return EnemyStateType::Wait;
	}

	return EnemyStateType::Attack1;
}

EnemyStateType HedgeHog::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
}

EnemyAIType HedgeHog::ChangeAIType()
{
	//Enemyの位置や向き、プレイヤーとの関係によって
	//次に使用するAIが変化する

	if (GetNowAI() == EnemyAIType::AI1) {
		return EnemyAIType::AI2;
	}
	else if (GetNowAI() == EnemyAIType::AI2) {
		return EnemyAIType::AI3;
	}
	else {
		return EnemyAIType::AI1;
	}

	return EnemyAIType::AI1;
}

void HedgeHog::CreateNeedle()
{
	Position b_pos;

	//発射位置調整
	b_pos.y = m_pos.y + M_NEEDLE_ADJUST_Y;

	if (m_direction == Direction::LEFT) {
		b_pos.x = m_map_pos + M_NEEDLE_ADJUST_X;
	}
	else {
		b_pos.x = m_map_pos - M_NEEDLE_ADJUST_X + m_draw_param.tex_size_x;
	}

	//Bullet(ハリ)生成
	CreateBullet(b_pos.x, b_pos.y, m_speed);
}

void HedgeHog::InitAllState()
{
	//ニードルリセット
	m_do_needle = false;
}

