#include"TrpPlayer.h"
#include"../Engine/Graphics.h"
//#include"../Texture/Texture.h"
#include"../Object/Definition.h"
#include"../Engine/Vec.h"
#include"../Engine/Input.h"
#include"../Map/Map.h"
#include"../Bullet/PlayerBullet.h"
#include "../DataBank/DataBank.h"
#include"../Manager/ObjectManager.h"



#include<string>



TrpPlayer::TrpPlayer()
{
	
}

TrpPlayer::~TrpPlayer()
{

}

void TrpPlayer::Init()
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
	m_draw_param.tex_size_x = 128.0f;
	timer = 70;
	timer2 = 0;
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

void TrpPlayer::Load()
{
	LoadTexture("Res/Tex/Player/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_RightTex);
	LoadTexture("Res/Tex/Player/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Attack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Attack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_RightTex);
	LoadTexture("Res/Tex/Player/Player_Damage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Damage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_RightTex);
	LoadTexture("Res/Tex/Player/Player_Jump_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Jump_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_RightTex);
	LoadTexture("Res/Tex/Player/Player_JumpAttack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_LeftTex);
	LoadTexture("Res/Tex/Player/Player_JumpAttack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_RightTex);
	LoadTexture("Res/Tex/Player/Player_JumpDamage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_LeftTex);
	LoadTexture("Res/Tex/Player/Player_JumpDamage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_RightTex);
	LoadTexture("Res/Tex/Player/Player_Walk_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Walk_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_RightTex);
	LoadTexture("Res/Tex/Effect/tyotyo01_E.png" ,TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
	LoadTexture("Res/Tex/Effect/tyotyo02_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_2Tex);
	LoadTexture("Res/Tex/Effect/tantyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_3Tex);
	LoadTexture("Res/Tex/Effect/tantyo02_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_4Tex);

}

void TrpPlayer::SetRectangle()
{
	m_rect_param.shift_x = 9.0f;
	m_rect_param.shift_y = 9.0f;
	m_rect_param.width = 114.0f;
	m_rect_param.height = 245.0f;
}

