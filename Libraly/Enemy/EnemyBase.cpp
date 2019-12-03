#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Refuge_Time	100				//逃げ回る時間
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

#define Fatigue_Gauge_Max 100		//疲労ゲージ上限
#define Sleep_Gauge_Max	100			//睡眠ゲージ上限

#define Attack_Interval 100			//攻撃感覚

TrpPlayer trpplayer;

//ここまで

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
	m_speed = 1.f;

	m_anim_timer = 0;

//	TrpPlayer* trpplayer;

	//	仮決め
	m_pos.x = 1000.0f;
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
	LoadTexture("Res/Tex/Boss1_Walk_Left.png",	TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBoss_WalkTex);
	LoadTexture("Res/Tex/Boss1_Tukare_Left.png",TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBoss_Fatigue);
	LoadTexture("Res/Tex/Boss1_Down_Left.png",	TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBoss_TaikiTex);
	LoadTexture("Res/Tex/Boss1_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBoss_SleepTex);
}

void EnemyBase::Update()
{
#if 1

	//Stateの遷移
	ChangeState();

#endif

	//現在の状態における動作の更新
	UpdateState();

	//アニメーション(パラパラ画像)値の更新
	AnimationUpdate();

}

void EnemyBase::Draw()
{
	//ObjectBase::Draw();

	//本来はObjectBaseにこの関数を置くのが適切
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

			//縦分割枚目が画像の分割数以上の場合
			if (m_draw_param.tv > M_ANIM_TEX_HEIGHT) {

				m_draw_param.tv = 1;

			}
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

void EnemyBase::UpdateState()		//エネミーの状態の更新
{
	//次の状態を示す変数
	EnemyStateType next_state = m_state;

	switch (m_state)
	{
	//待機状態
	case EnemyStateType::Wait:
		EnemyIdle();
		next_state = ChangeStateFromWait();
		break;

	//疲労待機状態
	case EnemyStateType::Rest:
		EnemyRest();
		next_state = ChangeStateFromRest();
		break;

	//移動状態
	case EnemyStateType::Warn:
		EnemyMove();
		next_state = ChangeStateFromWalk();
		break;

	//攻撃状態
	case EnemyStateType::Attack:
		EnemyAttack();
		next_state = ChangeStateFromAttack();
		break;

	//逃走状態(次のフェーズ移行？) ← ではなくゲージが一定以下の場合逃げる処理
	case EnemyStateType::Refuge:
		EnemyRefuge();
		next_state = ChangeStateFromRefuge();
		break;

	//追跡状態
	case EnemyStateType::Chase:
		next_state = ChangeStateFromChase();
		break;

	//睡眠状態(眠気度MAX)
	case EnemyStateType::Sleep:

		break;

	default:
		/*
			!!
		*/
		break;
	}

	/*
	//状態の変更
	if (m_state != next_state) {
		//next_sceneを専用の変数に渡し、状態遷移
		m_state = next_state;
	}
	*/

}

void EnemyBase::ChangeState()		//エネミーが行動する条件
{
	m_atk_time_count++;

	/*
		エネミーの状態の変更
	*/

	if (m_atk_time_count == 500 /*仮設定*/)
	{
		m_state = EnemyStateType::Attack;
		m_atk_time_count = 0;
	}

	/*
		11/29　田中コメントアウト
		m_centerXメンバが消えたことによって、エラー発生
		m_centerXメンバの代わりとなるものが必要
	*/

	if (m_is_break == true)
	{
		m_state = EnemyStateType::Rest;
	}
	else if (m_fatigue_gauge < Num_of_TakeaBreak)
	{
		m_state = EnemyStateType::Refuge;
	}
	else if (m_pos.x + Distance_of_Maintain < trpplayer.GetPos().x)
	{
		m_state = EnemyStateType::Chase;
	}
	else if (m_pos.x - Distance_of_Maintain > trpplayer.GetPos().x)
	{
		m_state = EnemyStateType::Chase;
	}
	else
	{
		m_state = EnemyStateType::Wait;	//処理のエラーの場合待機へ戻る。
	}
}
 
EnemyStateType EnemyBase::ChangeStateFromWait()
{
	return EnemyStateType::Wait;
}

EnemyStateType EnemyBase::ChangeStateFromWalk()
{
	return EnemyStateType::Warn;
}

EnemyStateType EnemyBase::ChangeStateFromRefuge() 
{
	return EnemyStateType::Refuge;
}

EnemyStateType EnemyBase::ChangeStateFromRest() 
{
	return EnemyStateType::Rest;
}

EnemyStateType EnemyBase::ChangeStateFromAttack()
{
	return EnemyStateType::Attack;
}

EnemyStateType EnemyBase::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
}

void EnemyBase::EnemyMove()			//エネミー移動
{
	/*
		通常状態のエネミー移動（適切な距離まで距離を詰める）
	*/


	if (trpplayer.GetPos().x > m_pos.x)
	{
		m_pos.x += m_speed;
	}
	else 
	{
		m_pos.x -= m_speed;
	}
}

#if 0
void EnemyBase::EnemyChase_R()
{
	/*
		敵が自分より右方向へ遠くにいる場合の追跡
	*/

	m_pos.x + m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

void EnemyBase::EnemyChase_L()
{
	/*
		敵が自分より左方向へ遠くにいる場合の追跡
	*/

	m_pos.x - m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

#endif

void EnemyBase::EnemyRefuge()		//疲労状態の逃走
{
	/*
		ピンチ状態のエネミー逃走
	*/

	m_refuge_time--;

	if (m_refuge_time == 0)
	{
		m_is_break = true;
		m_refuge_time = Refuge_Time;
	}
	else
	{
		/*
			enemy逃げる処理
		*/

		

		m_enemy_to_player_state = EnemytoPlayerState::Escape;

	}
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

void EnemyBase::EnemyRest()		//エネミー休憩
{
	/*
		エネミーの疲労待機（その場で疲労待機アニメーション）
	*/

	int cure_fatigue = Fatigue_Gauge_Max - m_fatigue_gauge;

	if (cure_fatigue > 0)
	{
		m_fatigue_gauge -= Cure_of_FatiguePoint * 5;	//だいたい通常回復の五倍くらい？
		cure_fatigue -= Cure_of_FatiguePoint * 5;
	}
	else
	{
		m_is_break = false;
	}
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

void EnemyBase::BackBeforeAttackState()
{
	EnemyStateType before_attack = GetEnemyState();

	m_state = EnemyStateType::Attack;
	/*
		各エネミー攻撃後にbefore_attackの中身をm_stateに反映する
	*/
}

