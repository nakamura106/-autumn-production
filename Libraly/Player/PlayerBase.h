#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"
#include"../Texture/Texture.h"
#include"../Bullet/PlayerBullet.h"
#include<vector>

const float G_PLAYER_SIZE = 256.0f;
const int G_NOTE_BOX_NUM = 3;

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	//!< 初期化関数
	virtual void Init() = 0;
	virtual void CreateBullets(PlayerBulletType bullettype);
	void Create();
	
	//!< アップデート関数(処理更新用)
	virtual void Update();
	//!< 描画関数(オブジェクトベースでまとめてやる予定)
	void Draw();
	//!< プレイヤーコントロール関数(プレイヤーの操作)
	void P_Controll();
	//!< プレイヤーのジャンプ処理関数
	virtual void Jump();
	//!< 弾が射程距離を超えたら音符ストックを消す関数
	void ReleaseNote();
	//状態遷移
	void ChangeState();
	
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

	virtual void InitWaitState();		
	virtual void InitMoveState();		
	virtual void InitJumpState();		
	virtual void InitJumpAttackState();	
	virtual void InitJumpDamageState();	
	virtual void InitDamageState();		
	virtual void InitAttackState();		
	virtual void InitMoveAttackState();
	virtual void InitThinkState();		
	virtual void InitDeathState();		
	virtual void InitClearState();		
	virtual void InitAllState();

	void Atkjudge();

	void BulletControl();

	void Attack();

	// エフェクト関係関数まとめただけの関数
	void AllInitEffect();
	void AllUpdateEffect();
	void AllDrawEffect();

	void CollisionParamUpdate()override;

	//2月14日　田中の雑コード
	virtual float GetHitUseAtk(ObjectRavel hit_obj_) {

		if (hit_obj_ == ObjectRavel::Ravel_MapObj) {
			if (m_map_pos + G_PLAYER_SIZE > 2354.f) {
				return 1.f;
			}
			return 0.f;
		}

		return m_hit_use_atk;
	}

protected:
	bool	m_do_jump;						//ジャンプ判定
	bool	m_is_miss;
	bool	m_is_active;					//動いているかの判定
	bool	m_play_note[2];					//音符生成
	bool	m_do_bullet_firing;				//攻撃判定用
	bool	m_is_release;					//音符開放判定用
	bool	m_do_attack;					//
	bool    m_is_hit_mapobj;
	int		m_hp;							//体力

	int		m_List;							//テクスチャーリスト保存用
	int		m_Key;							//長調か短調か
	int     m_i;							//アニメーション切り替え用
	int		m_play_note_timer;				//音符生成用タイマー
	int		m_release_timer;				//音符開解放用タイマー
	int		m_animtimer;
	int		m_effect;
	int		m_effecttimer;
	int		m_dmgeffecttimer;
	int		m_invincibletimer;
	float   m_floorpos;
	float	m_gravity;
	bool	m_is_obj_stop;					//マップオブジェクトに乗るためのflag
	bool	m_do_damage;					//ダメージを受けた時true

	int notebox[G_NOTE_BOX_NUM];

	std::vector<PlayerBullet*> bullet_list;

	void ClearAnimation() {};
	
private:
	const float M_BULLET_SPEED = 7.f;
	void ClearNoteBox();
};