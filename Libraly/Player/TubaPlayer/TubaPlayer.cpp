#include"TubaPlayer.h"
#include"../../Texture/Texture.h"
#include "../../Effect/Effects/SweatEffect.h"
#include "../../Manager/ObjectManager.h"



TubaPlayer::TubaPlayer()
{

}

TubaPlayer::~TubaPlayer()
{

}

void TubaPlayer::Init()
{
	m_is_delete = false;
	m_is_invincible = false;
	m_do_jump = false;
	m_is_active = false;
	m_is_release = false;
	m_do_attack = false;
	m_do_bullet_firing = false;
	m_hp = P_MaxHP;
	m_direction = RIGHT;
	m_speed = P_speed;
	m_state = (int)P_State::Wait;
	m_Key = (int)Key::Major;
	m_i = 0;
	m_map_pos = P_posX;
	m_pos.x = P_posX;
	m_pos.y = P_posYforest;
	m_draw_param.tex_size_x = 256.0f;
	m_List = GamePlayer_Taiki_RightTex;
	for (int i = 0; i < 2; i++)
	{
		m_play_note[i] = false;
	}
	for (int i = 0; i < 3; i++)
	{
		notebox[i] = 0;
	}
	Load();

	SetRectangle();

	
}

void TubaPlayer::Load()
{
	
}

void TubaPlayer::SetRectangle()
{
	m_rect_param.shift_x = 9.0f;
	m_rect_param.shift_y = 9.0f;
	m_rect_param.width = 114.0f;
	m_rect_param.height = 245.0f;
}

void TubaPlayer::Jump()
{
	
	static float jump_power = P_jump_power;

	m_anim_param.split_all = 20;
	m_anim_param.split_height = 5;

	//プレイヤーがDamage状態、Attack状態でなければジャンプ状態にする
	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump;
	}

	m_pos.y -= jump_power;
	jump_power -= Gravity;

	//プレイヤーが地面(ジャンプ開始前のY座標)についたらジャンプ状態を解除する
	if (m_pos.y >= P_posYforest)
	{
		jump_power = P_jump_power;
		m_do_jump = false;
		m_is_active = false;
	}
}