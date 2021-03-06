#include"PlayerBase.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include "../Effect/Effects/SweatEffect.h"
#include "../Effect/Effects/DebuffEffect.h"
#include "../Effect/Effects/FailureEffect.h"
#include "../Effect/Effects/LandingEffect.h"
#include "../Effect/Effects/ShotEffect.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Collision/ShapeType/ShapeRect.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/ObjectManager.h"
#include "../Sound/SoundManager.h"


PlayerBase::PlayerBase()
	:ObjectBase(ObjectRavel::Ravel_Player, Direction::RIGHT, P_speed, 0)
{
	//使用画像設定
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayer_Taiki_RightTex;
	m_draw_param.tex_size_x = G_PLAYER_SIZE;
	m_draw_param.tex_size_y = G_PLAYER_SIZE;

	//アニメーション用仮メンバ初期化
	m_anim_param.split_all = 12;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;
	m_anim_param.change_flame = Dispflame;

	m_effect = (int)P_effect::None;

	m_shape_list.push_back(new ShapeCircle(m_pos.x, 61.0f, m_pos.y, 57.0f, 39.0f, 256.0f));
	m_shape_list.push_back(new ShapeRect(m_pos.x, 61.0f, m_pos.y, 144.0f, 61.0f, 94.0f, 256.0f));
	m_shape_list.push_back(new ShapeCircle(m_pos.x, 65.0f, m_pos.y, 222.0f, 26.0f, 256.0f));
	
	
	m_animtimer = 0;
	m_floorpos = P_posYforest;
	m_effecttimer = 16;
	m_dmgeffecttimer = 61;
	m_invincibletimer = 0;
	m_gravity = 17.0f;
	m_is_miss = false;
	m_is_hit_mapobj = false;
	m_is_obj_stop = false;
	m_do_damage = false;
	AllInitEffect();
	m_is_invincible == false;
	
}

PlayerBase::~PlayerBase()
{
	//bullet解放
	for (auto& i : bullet_list) {
		delete i;
		i = nullptr;
	}
	std::vector<PlayerBullet*>().swap(bullet_list);
}
void PlayerBase::Create()
{

}

void PlayerBase::Update()
{
	DataBank::Instance()->SetPlayerHp(m_hp);
	DataBank::Instance()->SetPlayerMapPos(m_map_pos);
	DataBank::Instance()->SetNote(notebox[0], notebox[1], notebox[2]);
	DataBank::Instance()->SetPlayerDirection(m_direction);
	ObjectBase::Update();
	BulletControl();
	if (m_hp > 0)
	{
		P_Controll();
		Atkjudge();
		CollisionParamUpdate();
		AllUpdateEffect();
		ChangeState();
	}
	else if(m_hp==0||DataBank::Instance()->GetIsGameOver()==true)
	{
		m_state = (int)P_State::Wait;
		ChangeState();
		ChangeSceneStep(SceneStep::EndStep);
	}
	if (DataBank::Instance()->GetIsGameClear()==true)
	{
		m_anim_param.split_all = 20;
		m_anim_param.split_height = 4;
		m_state = (int)P_State::Clear;
		ChangeState();
	}
	AnimationUpdate();

}

void PlayerBase::BulletControl()
{
	for (int i = 0; i < static_cast<int>(bullet_list.size()); ++i) {
		//弾の更新
		bullet_list[i]->Update();

		//弾のis_deleteがtrueの場合、弾消滅
		if (bullet_list[i]->GetIsDelete()) {
			//メモリ解放
			delete bullet_list[i];

			//弾を消滅
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}

void PlayerBase::Draw()
{
	
	ObjectBase::Draw();

	for (const auto& i : bullet_list) {

		if (i != nullptr) {
			i->Draw();
		}

	}
	if (m_hp > 0)
	{
		AllDrawEffect();
	}

}

void PlayerBase::P_Controll()
{
	if (m_play_note_timer <= 70)
	{
		m_play_note_timer++;
	}

	if (m_effecttimer <= 16)
	{
		m_effecttimer++;
	}
	if (m_dmgeffecttimer <= 61)
	{
		m_dmgeffecttimer++;
	}

	if (m_invincibletimer >= 0)
	{
		m_invincibletimer--;
	}
	if (m_invincibletimer == 0)
	{
		m_is_invincible = false;
	}
	
	DataBank::Instance()->SetState(m_state);

	/*ボタンを離した後にモーションが
	継続してしまわないようにする処理*/
	if (m_is_active == true)
	{
		m_is_active = false;
	}
	
	// ※までボタン処理


	if (GetKey(A_KEY) == true)
	{
		ChangeSceneStep(SceneStep::EndStep);
	}

	

	//右移動
	if ((IsButtonPush(RightButton)||GetKey(RIGHT_KEY) == true)&&m_state!=(int)P_State::Attack)
	{
		m_state = (int)P_State::Move;
		DataBank::Instance()->SetState(m_state);
		if (DataBank::Instance()->GetfgPos() >= 0 || DataBank::Instance()->GetfgPos() <= -3550.0f )
		{
			m_pos.x += m_speed;
		}
		if (m_direction == LEFT) {
			m_pos.x += lrAdjustment;
		}
		if (m_map_pos < 3550.0f)
		{
			m_map_pos += m_speed;
		}
		m_direction = RIGHT;
		m_is_active = true;
	}

	//左移動
	else if ((IsButtonPush(LeftButton)  || GetKey(LEFT_KEY) == true) && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Move;
		DataBank::Instance()->SetState(m_state);
		if (DataBank::Instance()->GetfgPos() <= -3550.0f || DataBank::Instance()->GetfgPos() >= 0)
		{
			m_pos.x -= m_speed;
		}
		if (m_direction == RIGHT) {
			m_pos.x -= lrAdjustment;
		}
		if (m_map_pos > 0.0f)
		{
			m_map_pos -= m_speed;
		}
		
		m_direction = LEFT;
		
		m_is_active = true;
	}

	//プレイヤーに重力をかける処理

	m_pos.y += m_gravity;
	m_gravity += Gravity;

	if (m_pos.y >= P_posYforest && m_is_obj_stop != true) {
		m_pos.y = P_posYforest;
		m_gravity = 0.f;
	}

	//ジャンプ処理
	if ((IsButtonPush(AButton) == true || GetKeyDown(SPACE_KEY) == true) && m_do_jump != true)
	{
		m_do_jump = true;
		m_is_active = true;
		m_gravity = -P_jump_power;
		m_pos.y -= 1.f;
		InitAllState();
		if (m_is_obj_stop == true) {
			m_is_obj_stop = false;
		}
	}

	if (m_is_hit_mapobj == true) {

		if (m_gravity > 0.f) {
			//stop処理
			m_is_obj_stop = true;
		}

		if (m_is_obj_stop == true && m_pos.y <= m_floorpos - m_draw_param.tex_size_y) {
			m_pos.y = m_floorpos - m_draw_param.tex_size_y;

			m_gravity = 0.f;
		}
		/*if (m_pos.y + m_draw_param.tex_size_y >= m_floorpos && m_gravity > 0.f) {

			m_pos.y = m_floorpos - m_draw_param.tex_size_y;
			m_do_jump = false;
			m_is_active = false;
			m_gravity = 0.f;
		}

		if (m_do_jump != true) {
			m_gravity = 0.f;
		}*/
	}
	else {
		m_is_obj_stop = false;
	}

	
	
	//長調短調切り替え処理(押している間のみ)


	//音符生成
	if (IsButtonDown(BButton) || GetKeyDown(ONE_KEY) == true)
	{
		if (m_play_note_timer >= 70)
		{
			m_play_note[0] = true;
			m_play_note_timer = 0;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					if (i == 0) {
						SoundManager::Instance()->SoundBullet1SE();
					}
					else if (i == 1) {
						SoundManager::Instance()->SoundBullet2SE();
					}
					else {
						SoundManager::Instance()->SoundBullet3SE();
					}
					break;
				}
			}
		}
		
	}
	if (IsButtonDown(YButton)==true||GetKeyDown(TWO_KEY)==true)
	{
		if (m_play_note_timer >= 70)
		{
			m_play_note[1] = true;
			m_play_note_timer = 0;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = B;
					if (i == 0) {
						SoundManager::Instance()->SoundBullet1SE();
					}
					else if (i == 1) {
						SoundManager::Instance()->SoundBullet2SE();
					}
					else {
						SoundManager::Instance()->SoundBullet3SE();
					}
					break;
				}
			}
		}
	}

	// ※
	
	
	//activeがfalseなら待機状態にする処理
	if (m_is_active == false&& m_state != (int)P_State::Wait)
	{	
		m_state = (int)P_State::Wait;
		DataBank::Instance()->SetState(m_state);
	}

	if (m_do_jump == true)
	{
		Jump();
	}
	//プレイヤーがジャンプしているか判定する(しているならジャンプ関数を呼び出す)
	if (m_is_animation_end == true)
	{
		m_anim_param.split_all = 12;
		m_anim_param.split_height = 4;
	}

	if (m_do_attack == true)
	{
		m_animtimer++;
		Attack();
	}

	//画面端との当たり判定
	if (m_pos.x <= -lrAdjustment - 7)
	{
		m_pos.x += m_speed;
	}

	if (m_pos.x >= 1800.0f)
	{
		m_pos.x -= m_speed;
	}

	
	

	m_is_hit_mapobj = false;
}

void PlayerBase::CreateBullets(PlayerBulletType bullettype)
{
	Position b_pos;
	if (m_direction == Direction::LEFT) {
		b_pos.x = m_map_pos - m_draw_param.tex_size_x/2.0f;
		b_pos.y = m_pos.y;
	}
	else {
		b_pos.x = m_map_pos + m_draw_param.tex_size_x/2.0f;
		b_pos.y = m_pos.y;
	}

	//Bullet(弾)生成

	bullet_list.push_back(new PlayerBullet(b_pos.x, b_pos.y, M_BULLET_SPEED, (Direction)m_direction, bullettype));

}

void PlayerBase::Atkjudge()
{
	if (notebox[0] == A && notebox[1] == A && notebox[2] == A || notebox[0] == A && notebox[1] == B && notebox[2] == A)
	{

		if (m_is_release == false)
		{
			m_release_timer++;
		}
		if (notebox[1] == A)
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//弾発射
				CreateBullets(PlayerBulletType::Chocho_1);
				m_do_attack = true;
				m_is_active = true;
				InitAllState();
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
		else
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//弾発射
				CreateBullets(PlayerBulletType::Chocho_2);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
	}

	if (notebox[0] == B && notebox[1] == B && notebox[2] == B || notebox[0] == B && notebox[1] == A && notebox[2] == B)
	{

		if (m_is_release == false)
		{
			m_release_timer++;
		}
		if (notebox[1] == B)
		{


			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//弾発射
				CreateBullets(PlayerBulletType::Tancho_1);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
		else
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//弾発射
				CreateBullets(PlayerBulletType::Tancho_2);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
	}

	if (notebox[0] == A && notebox[1] == A && notebox[2] == B || notebox[0] == A && notebox[1] == B && notebox[2] == B ||
		notebox[0] == B && notebox[1] == B && notebox[2] == A || notebox[0] == B && notebox[1] == A && notebox[2] == A)
	{
		
		if (m_is_release == false)
		{
			m_is_miss = true;
			m_release_timer++;

		}
		if (m_release_timer >= 140)
		{
			m_is_miss = false;
			m_is_release = true;
			ReleaseNote();
		}	
	}
}

void PlayerBase::ReleaseNote()
{
	m_release_timer = 0;

	//音符の演奏(ストック)をすべて破棄する
	for (int i = 0; i < 3; i++)
	{
		notebox[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		m_play_note[i] = false;
	}
	m_do_bullet_firing = false;

	m_is_release = false;

}

void PlayerBase::Jump()
{
	static float jump_power = P_jump_power;

	if (DataBank::Instance()->GetPlayerType() == (int)Player::PlayerTypeTuba)
	{
		m_anim_param.split_all = 20;
		m_anim_param.split_height = 5;
	}

	//プレイヤーがDamage状態、Attack状態でなければジャンプ状態にする
	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump;
		DataBank::Instance()->SetState(m_state);
	}
	if (m_do_jump == true && m_state == (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump_Attack;
		DataBank::Instance()->SetState(m_state);
	}
	if (m_do_jump == true && m_state == (int)P_State::Damage)
	{
		m_state = (int)P_State::Jump_Damage;
		DataBank::Instance()->SetState(m_state);
	}


	//プレイヤーが地面(ジャンプ開始前のY座標)についたらジャンプ状態を解除する
	if (m_pos.y >= P_posYforest || m_is_obj_stop == true)
	{
		m_effecttimer = 0;
		m_anim_param.split_all = 12;
		m_anim_param.split_height = 4;
		m_do_jump = false;
		m_is_active = false;
	}
}

void PlayerBase::Attack()
{
	if (m_animtimer >= 72)
	{
		m_do_attack = false;
		m_is_active = false;
		m_animtimer = 0;
	}
	if (GetKey(LEFT_KEY) == true || GetKey(RIGHT_KEY) == true||IsButtonPush(LeftButton)||IsButtonPush(RightButton))
	{
		if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
		{
			m_state = (int)P_State::Move_Attack;
			DataBank::Instance()->SetState(m_state);
		}
	}
	else if (m_state != (int)P_State::Damage&&m_state!=(int)P_State::Attack )
	{
		m_state = (int)P_State::Attack;
		DataBank::Instance()->SetState(m_state);
	}
	
}

void PlayerBase::AllInitEffect()
{
	m_effect_list.push_back(new SweatEffect(this));
	m_effect_list.push_back(new DebuffEffect(this));
	m_effect_list.push_back(new FailureEffect(this));
	m_effect_list.push_back(new LandingEffect(this));
	m_effect_list.push_back(new ShotEffect(this));
}

void PlayerBase::AllUpdateEffect()
{
	// エフェクト条件
	// HP１の時のエフェクト条件
	if (m_hp == 1) {
		m_effect_list.at(0)->WakeUp();
	}
	else {
		m_effect_list.at(0)->Sleep();
	}
	//演奏失敗時
	if (m_is_miss==true)
	{
		m_effect_list.at(2)->WakeUp();
	}
	else
	{
		m_effect_list.at(2)->Sleep();
	}
	//着地時
	if (m_effecttimer <= 15)
	{
		m_effect_list.at(3)->WakeUp();
	}
	else
	{
		m_effect_list.at(3)->Sleep();
	}
	// 被弾時エフェクト条件
	if (m_dmgeffecttimer<=60)
	{
		
		m_effect_list.at(4)->WakeUp();
	}
	else 
	{
		m_effect_list.at(4)->Sleep();
	}



	m_effect_list.at(0)->Update();
	m_effect_list.at(1)->Update();
	m_effect_list.at(2)->Update();
	m_effect_list.at(3)->Update();
	m_effect_list.at(4)->Update();
}

void PlayerBase::AllDrawEffect()
{
		m_effect_list.at(0)->Draw();
		m_effect_list.at(1)->Draw();
		m_effect_list.at(2)->Draw();
		m_effect_list.at(3)->Draw();
		m_effect_list.at(4)->Draw();
}

void PlayerBase::CollisionParamUpdate()
{
	for (const auto& i : m_shape_list)
	{
		i->Update(m_pos.x, m_pos.y, m_direction);
	}
	CollisionManager::GetInstance().AddPlayerColObject(this);
}

void PlayerBase::ClearNoteBox()
{
	for (int i = 0;i < G_NOTE_BOX_NUM;++i) {
		notebox[i] = 0;
	}
}

void PlayerBase::InitWaitState() 
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Taiki_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Taiki_RightTex;
	}
}

void PlayerBase::InitMoveState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Walk_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Walk_RightTex;
	}

}

void PlayerBase::InitJumpState() 
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Jump_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Jump_RightTex;
	}
}

void PlayerBase::InitJumpAttackState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_JumpAttack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_JumpAttack_RightTex;
	}
}

void PlayerBase::InitJumpDamageState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_JumpDamage_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_JumpDamage_RightTex;
	}
}

void PlayerBase::InitDamageState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Damage_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Damage_RightTex;
	}
}

void PlayerBase::InitAttackState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Attack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Attack_RightTex;
	}
}

void PlayerBase::InitMoveAttackState()
{

	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_WalkAttack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_WalkAttack_RightTex;
	}
}

void PlayerBase::InitThinkState()
{
	
	if (m_direction == Direction::LEFT)
	{
		
	}
	if (m_direction == Direction::RIGHT)
	{

	}
}

void PlayerBase::InitDeathState()
{
	
	if (m_direction == Direction::LEFT)
	{
	
	}
	if (m_direction == Direction::RIGHT)
	{

	}
}

void PlayerBase::InitClearState()
{

	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Clear_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Clear_RightTex;
	}
}

void PlayerBase::ChangeState()
{
	

	switch (m_state)
	{
	case (int)P_State::Wait:
		InitWaitState();
		break;
	case (int)P_State::Move:
		InitMoveState();
		break;
	case (int)P_State::Jump:
		InitJumpState();
		break;
	case (int)P_State::Attack:
		InitAttackState();
		break;
	case (int)P_State::Move_Attack:
		InitMoveAttackState();
		break;
	case (int)P_State::Damage:
		InitDamageState();
		break;
	case (int)P_State::Jump_Damage:
		InitJumpDamageState();
		break;
	case (int)P_State::Jump_Attack:
		InitJumpAttackState();
		break;
	case (int)P_State::Clear:
		InitClearState();
		break;
	case (int)P_State::Death:
		InitDeathState();
		break;	
	default:
		break;
	}

	
}

void PlayerBase::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{
	if (ravel_ == ObjectRavel::Ravel_MapObj ) {

		m_floorpos = hit_use_atk_ + 34.f;

		m_is_hit_mapobj = true;
	}

	if (ravel_ == ObjectRavel::Ravel_EnemyBullet || ravel_ == ObjectRavel::Ravel_Boss)
	{
		if (m_invincibletimer <= 0 && m_hp>=0)
		{
			m_hp--;
			DataBank::Instance()->SetPlayerHp(m_hp);
			m_dmgeffecttimer = 0;
		}
		if (m_is_invincible==false)
		{
			m_invincibletimer = 90;
			m_is_invincible == true;
		}
		m_invincibletimer--;
	}
	else if (ravel_ == ObjectRavel::Ravel_Boss || ravel_ == ObjectRavel::Ravel_EnemyBullet) {
		if (hit_use_atk_ > 0.f && m_do_damage == false) {

			//ダメージ
			--m_hp;

			//ダメージ受けたフラグON
			m_do_damage = true;
		}
	}
	else if (ravel_ == ObjectRavel::Ravel_BananaBullet) {
		//速度低下・音符ストック消去
		ClearNoteBox();
	}
	else if (ravel_ == ObjectRavel::Ravel_ShitBullet) {
		//演奏・ジャンプ禁止・音符ストック消去
		ClearNoteBox();
	}

}

void PlayerBase::InitAllState()
{
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
}

