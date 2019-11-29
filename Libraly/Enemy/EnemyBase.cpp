#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

//仮変数（定数）用意できたら消す分

const int player_pos_x = 100;
const int player_pos_y = 100;

//ここまで

TrpPlayer trpplayer;

EnemyBase::EnemyBase()
{
	m_enemy_id = EnemyID::BossTypeMax;
	m_state = EnemyStateType::EnemyStateTypeMax;
	m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = 0.f;
	m_sleep_gauge = 0.f;
	m_time_of_break = 0;
	m_is_break = false;
	m_is_delete = false;
	m_is_hit_judge = false;

	m_anim_timer = 0;

	//	仮決め
	m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	

	//描画情報格納
	m_draw_param.tu = 1;
	m_draw_param.tv = 1;
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GameBoss_WalkTex;
	
}

EnemyBase::~EnemyBase()
{
	
}

void EnemyBase::Init()
{
	/*11/26 注!!仮実装のコード*/
	LoadTexture("Res/Tex/Boss1_Walk_Left.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void EnemyBase::Update()
{
	AnimationUpdate();
}

void EnemyBase::Draw()
{
	//ObjectBase::Draw();

	DrawUVTexture(
		m_pos.x, 
		m_pos.y, 
		M_ENEMY_SYZE, 
		M_ENEMY_SYZE, 
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id), 
		m_draw_param.tu / M_ANIM_TEX_WIDTH, 
		m_draw_param.tv / M_ANIM_TEX_HEIGHT
	);

}

void EnemyBase::AnimationUpdate() {

	++m_anim_timer;

	if (m_anim_timer >= M_ANIM_FLAME) {//画像を変更する

		m_anim_timer = 0;

		//横分割枚目を加算
		++m_draw_param.tu;

		//横分割枚目が画像の分割数以上の場合
		if (m_draw_param.tu > M_ANIM_TEX_WIDTH) {

			m_draw_param.tu = 1;

			//縦分割枚目を加算
			++m_draw_param.tv;
		}

		//縦分割枚目が画像の分割数以上の場合
		if (m_draw_param.tv > M_ANIM_TEX_HEIGHT) {

			m_draw_param.tv = 1;

		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (((m_draw_param.tv - 1) * M_ANIM_TEX_WIDTH + m_draw_param.tu) > M_ANIM_TEX_ALL) {

			m_draw_param.tu = m_draw_param.tv = 1;

		}

	}

}


EnemyStateType EnemyBase::GetEnemyState()	//エネミーの状態を取得
{
	return m_state;
}

//	～ここまで～

void EnemyBase::UpdateState()		//エネミーの状態の更新	//必要？？
{
	switch (m_state)
	{
	case EnemyStateType::Idle:

		EnemyIdle();

		break;

	case EnemyStateType::Break:

		EnemyBreak();

		break;

	case EnemyStateType::Warn:

		EnemyMove();

		break;

	case EnemyStateType::Attack:

		EnemyAttack();

		break;

	case EnemyStateType::Refuge:

		EnemyRefuge();

		break;

	default:
		/*
			!!
		*/
		break;
	}
}

void EnemyBase::ChangeState()		//エネミーが行動する条件
{
	/*
		エネミーの状態の変更
	*/

	if (m_fatigue_gauge <= Num_of_TakeaBreak)
	{
		if (m_time_of_break < Limit_of_BreakTime)
		{
			m_is_break = true;
			m_state = EnemyStateType::Break;
			m_time_of_break++;
		}
		else if (m_is_break == true)
		{
			m_state = EnemyStateType::Refuge;
			m_time_of_break--;
			if (m_time_of_break == 0)
			{
				m_is_break = false;
			}
		}
	}

	/*
		プレイヤーの位置情報を取得して、適切な距離を保つ。
	*/
}

void EnemyBase::EnemyMove()			//エネミー移動
{
	/*
		通常状態のエネミー移動（適切な距離まで距離を詰める）
	*/

	if (m_pos.x < player_pos_x + Distance_of_Maintain || m_pos.x < player_pos_x - Distance_of_Maintain)
	{
		m_pos.x;		//書きかけ
	}

}

void EnemyBase::EnemyRefuge()		//疲労状態の逃走
{
	/*
		ピンチ状態のエネミー逃走
	*/



}

void EnemyBase::EnemyAttack()		//エネミー攻撃
{
	/*
		敵からプレイヤーへの状態に応じて攻撃種を変更
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Close:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Escape:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Pursue:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;


	default:
		/*
			!!
		*/
		break;
	}

}

void EnemyBase::EnemyIdle()			//エネミー待機
{
	/*
		エネミーの待機（その場で待機アニメーション）
	*/



}

void EnemyBase::EnemyBreak()		//エネミー休憩
{
	/*
		エネミーの疲労待機（その場で疲労待機アニメーション）
	*/



}

void EnemyBase::CureSleepiness()
{
	m_sleep_gauge -= Cure_of_SleepinessPoint;
}

void EnemyBase::CureFatigue()
{
	m_fatigue_gauge -= Cure_of_FatiguePoint;
}

void EnemyBase::DamageSleepness(int damage_sleep_)
{
	m_sleep_gauge += damage_sleep_;
}

void EnemyBase::DamageFatigue(int damage_fatigue_)
{
	m_fatigue_gauge += damage_fatigue_;
}


