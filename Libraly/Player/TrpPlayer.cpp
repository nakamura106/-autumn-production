#include"TrpPlayer.h"
#include"../Engine/Graphics.h"
#include"../Texture/Texture.h"
#include"../Object/Definition.h"
#include"../Engine/Vec.h"

TrpPlayer trpplayer;

Direction direction;



Vec2 vec2;

TrpPlayer::TrpPlayer()
{
	
}

TrpPlayer::~TrpPlayer()
{

}

void TrpPlayer::Init()
{
	trpplayer.m_is_delete = true;
	trpplayer.m_is_invincible = true;
	trpplayer.m_hp = 0;
	trpplayer.m_direction = RIGHT;
	trpplayer.m_state = (int)P_State::Wait;
	trpplayer.m_pos.x = 0;
	trpplayer.m_pos.y = 0;
	trpplayer.m_centerX = 0;
	trpplayer.m_centerY = 0;
	trpplayer.m_sprite_width = 0;
	trpplayer.m_sprite_height = 0;
	trpplayer.m_range = 0;
	trpplayer.m_speed = 0;
	trpplayer.m_tu = 0;
	trpplayer.m_tv = 0;
	Load();
	Create();
}

void TrpPlayer::Load()
{
	LoadTexture("Res/Tex/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_LeftTex);

}

void TrpPlayer::Create()
{
	trpplayer.m_is_delete = false;
	trpplayer.m_is_invincible = false;
	trpplayer.m_hp = 5;
	trpplayer.m_direction = RIGHT;
	trpplayer.m_state = (int)P_State::Wait;
	trpplayer.m_pos.x = P_posX;
	trpplayer.m_pos.y = P_posY;
	trpplayer.m_centerX = trpplayer.m_pos.x+128.0f;
	trpplayer.m_centerY = trpplayer.m_pos.y+128.0f;
	trpplayer.m_sprite_width = 256.0f;
	trpplayer.m_sprite_height = 256.0f;
	trpplayer.m_range = P_trp_range;
	trpplayer.m_speed = P_speed;
}

void TrpPlayer::Update()
{

}

void TrpPlayer::Draw()
{
	//DrawTexture(0, 0, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_RightTex));

	DrawUVTexture(trpplayer.m_pos.x, trpplayer.m_pos.y,trpplayer.m_sprite_width,trpplayer.m_sprite_height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_RightTex),trpplayer.m_tu,trpplayer.m_tv,trpplayer.m_direction);
}

Position TrpPlayer::GetPos()
{
	return m_pos;
}