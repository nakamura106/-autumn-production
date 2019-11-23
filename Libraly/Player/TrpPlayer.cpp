#include"TrpPlayer.h"
#include"../Engine/Graphics.h"
#include"../Texture/Texture.h"
#include"../Object/Definition.h"
#include"../Engine/Vec.h"
#include"../Engine/Input.h"





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
	m_hp = 5;
	m_direction = RIGHT;
	m_state = (int)P_State::Wait;
	m_pos.x = P_posX;
	m_pos.y = P_posY;
	m_centerX = m_pos.x + 128.0f;
	m_centerY = m_pos.y + 128.0f;
	m_sprite_width = 256.0f;
	m_sprite_height = 256.0f;
	m_range = P_trp_range;
	Load();
	InitAnimation();
}

void TrpPlayer::Load()
{
	LoadTexture("Res/Tex/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_LeftTex);

}

void TrpPlayer::Create()
{
	
	
}

void TrpPlayer::Update()
{
	P_Controll();
}

void TrpPlayer::Draw()
{
	if (m_is_delete==false)
	{
		WaitAnimation();
	}
}

Position TrpPlayer::GetPos()
{
	return m_pos;
}

void TrpPlayer::P_Controll()
{
	if (GetKey(LEFT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		m_direction = LEFT;
		m_pos.x -= P_speed;
	}
	if (GetKey(RIGHT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		m_direction = RIGHT;
		m_pos.x += P_speed;
	}
	if (GetKey(SPACE_KEY) == true)
	{
		m_state = (int)P_State::Jump;
	}
}

void TrpPlayer::InitAnimation()
{
	InitWaitAnimation();
}

void TrpPlayer::InitWaitAnimation()
{
	
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{

		wait_animation_Right[i].m_RectX = R_X;
		wait_animation_Right[i].m_RectY = R_Y;
		wait_animation_Right[i].m_Rect_Height = Rect_Height;
		wait_animation_Right[i].m_Rect_Width = Rect_Width;
		wait_animation_Right[i].m_Display_Flame = Dispflame;

		wait_animation_Left[i].m_RectX = R_X;
		wait_animation_Left[i].m_RectY = R_Y;
		wait_animation_Left[i].m_Rect_Height = Rect_Height;
		wait_animation_Left[i].m_Rect_Width = Rect_Width;
		wait_animation_Left[i].m_Display_Flame = Dispflame;

		R_X += RectX;


		if (R_X >= 1.0f)
		{
			if (R_Y <= 0.75f)
			{
				R_Y += RectY;
			}
			else
			{
				R_Y = 0;
			}

			R_X = 0;
		}




	}

}
void TrpPlayer::WaitAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, wait_animation_Right[i].m_Rect_Width, wait_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_RightTex), wait_animation_Right[i].m_RectX, wait_animation_Right[i].m_RectY);
		wait_animation_Right[i].m_Display_Flame--;
		if (wait_animation_Right[i].m_Display_Flame <= 0)
		{
			wait_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x-128, m_pos.y, wait_animation_Left[j].m_Rect_Width, wait_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_LeftTex), wait_animation_Left[j].m_RectX, wait_animation_Left[j].m_RectY);
		wait_animation_Left[j].m_Display_Flame--;
		if (wait_animation_Left[j].m_Display_Flame <= 0)
		{
			wait_animation_Left[j].m_Display_Flame = Dispflame;
			
			j++;
			if (j >= 11)
			{
				j = 0;
			}
			
		}
	}

	
}

void TrpPlayer::InitMoveAnimation()
{
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{
		
		move_animation_Right[i].m_RectX = R_X;
		move_animation_Right[i].m_RectY = R_Y;
		move_animation_Right[i].m_Rect_Height = Rect_Height;
		move_animation_Right[i].m_Rect_Width = Rect_Width;
		move_animation_Right[i].m_Display_Flame = 6;
		

		
		move_animation_Left[i].m_RectX = R_X;
		move_animation_Left[i].m_RectY = R_Y;
		move_animation_Left[i].m_Rect_Height = Rect_Height;
		move_animation_Left[i].m_Rect_Width = Rect_Width;
		move_animation_Left[i].m_Display_Flame = 6;
		
	}
	
	R_X += RectX;


	if (R_X >= 1.0f)
	{
		if (R_Y <= 0.75f)
		{
			R_Y += RectY;
		}
		else
		{
			R_Y = 0;
		}

		R_X = 0;
	}
	

}
void TrpPlayer::InitJumpAnimation()
{
	move_animation_Right[0].m_Rect_Num = 0;
	move_animation_Right[0].m_RectX = 0.25f;
	move_animation_Right[0].m_RectY = 0.0f;
	move_animation_Right[0].m_Rect_Height = 256.0f;
	move_animation_Right[0].m_Rect_Width = 256.0f;
	move_animation_Right[0].m_Display_Flame = 6;
	move_animation_Right[0].Next_Rect_Num = 1;

	move_animation_Right[1].m_Rect_Num = 1;
	move_animation_Right[1].m_RectX = 0.5f;
	move_animation_Right[1].m_RectY = 0.0f;
	move_animation_Right[1].m_Rect_Height = 256.0f;
	move_animation_Right[1].m_Rect_Width = 256.0f;
	move_animation_Right[1].m_Display_Flame = 6;
	move_animation_Right[1].Next_Rect_Num = 2;

	move_animation_Right[2].m_Rect_Num = 2;
	move_animation_Right[2].m_RectX = 0.75f;
	move_animation_Right[2].m_RectY = 0.0f;
	move_animation_Right[2].m_Rect_Height = 256.0f;
	move_animation_Right[2].m_Rect_Width = 256.0f;
	move_animation_Right[2].m_Display_Flame = 6;
	move_animation_Right[2].Next_Rect_Num = 3;

	move_animation_Right[3].m_Rect_Num = 3;
	move_animation_Right[3].m_RectX = 1.0f;
	move_animation_Right[3].m_RectY = 0.0f;
	move_animation_Right[3].m_Rect_Height = 256.0f;
	move_animation_Right[3].m_Rect_Width = 256.0f;
	move_animation_Right[3].m_Display_Flame = 6;
	move_animation_Right[3].Next_Rect_Num = 4;

	wait_animation_Right[4].m_Rect_Num = 4;
	wait_animation_Right[4].m_RectX = 0.25f;
	wait_animation_Right[4].m_RectY = 0.25f;
	wait_animation_Right[4].m_Rect_Height = 256.0f;
	wait_animation_Right[4].m_Rect_Width = 256.0f;
	wait_animation_Right[4].m_Display_Flame = 6;
	wait_animation_Right[4].Next_Rect_Num = 5;

	move_animation_Right[5].m_Rect_Num = 5;
	move_animation_Right[5].m_RectX = 0.5f;
	move_animation_Right[5].m_RectY = 0.25f;
	move_animation_Right[5].m_Rect_Height = 256.0f;
	move_animation_Right[5].m_Rect_Width = 256.0f;
	move_animation_Right[5].m_Display_Flame = 6;
	move_animation_Right[5].Next_Rect_Num = 6;

	move_animation_Right[6].m_Rect_Num = 6;
	move_animation_Right[6].m_RectX = 0.75f;
	move_animation_Right[6].m_RectY = 0.25f;
	move_animation_Right[6].m_Rect_Height = 256.0f;
	move_animation_Right[6].m_Rect_Width = 256.0f;
	move_animation_Right[6].m_Display_Flame = 6;
	move_animation_Right[6].Next_Rect_Num = 7;

	move_animation_Right[7].m_Rect_Num = 7;
	move_animation_Right[7].m_RectX = 1.0f;
	move_animation_Right[7].m_RectY = 0.25f;
	move_animation_Right[7].m_Rect_Height = 256.0f;
	move_animation_Right[7].m_Rect_Width = 256.0f;
	move_animation_Right[7].m_Display_Flame = 6;
	move_animation_Right[7].Next_Rect_Num = 8;

	move_animation_Right[8].m_Rect_Num = 8;
	move_animation_Right[8].m_RectX = 0.25f;
	move_animation_Right[8].m_RectY = 0.5f;
	move_animation_Right[8].m_Rect_Height = 256.0f;
	move_animation_Right[8].m_Rect_Width = 256.0f;
	move_animation_Right[8].m_Display_Flame = 6;
	move_animation_Right[8].Next_Rect_Num = 9;

	move_animation_Right[9].m_Rect_Num = 9;
	move_animation_Right[9].m_RectX = 0.5f;
	move_animation_Right[9].m_RectY = 0.5f;
	move_animation_Right[9].m_Rect_Height = 256.0f;
	move_animation_Right[9].m_Rect_Width = 256.0f;
	move_animation_Right[9].m_Display_Flame = 6;
	move_animation_Right[9].Next_Rect_Num = 10;

	move_animation_Right[10].m_Rect_Num = 10;
	move_animation_Right[10].m_RectX = 0.75f;
	move_animation_Right[10].m_RectY = 0.5f;
	move_animation_Right[10].m_Rect_Height = 256.0f;
	move_animation_Right[10].m_Rect_Width = 256.0f;
	move_animation_Right[10].m_Display_Flame = 6;
	move_animation_Right[10].Next_Rect_Num = 0;


	move_animation_Left[0].m_Rect_Num = 0;
	move_animation_Left[0].m_RectX = 0.25f;
	move_animation_Left[0].m_RectY = 0.0f;
	move_animation_Left[0].m_Rect_Height = 256.0f;
	move_animation_Left[0].m_Rect_Width = 256.0f;
	move_animation_Left[0].m_Display_Flame = 6;
	move_animation_Left[0].Next_Rect_Num = 1;

	move_animation_Left[1].m_Rect_Num = 1;
	move_animation_Left[1].m_RectX = 0.5f;
	move_animation_Left[1].m_RectY = 0.0f;
	move_animation_Left[1].m_Rect_Height = 256.0f;
	move_animation_Left[1].m_Rect_Width = 256.0f;
	move_animation_Left[1].m_Display_Flame = 6;
	move_animation_Left[1].Next_Rect_Num = 2;

	move_animation_Left[2].m_Rect_Num = 2;
	move_animation_Left[2].m_RectX = 0.75f;
	move_animation_Left[2].m_RectY = 0.0f;
	move_animation_Left[2].m_Rect_Height = 256.0f;
	move_animation_Left[2].m_Rect_Width = 256.0f;
	move_animation_Left[2].m_Display_Flame = 6;
	move_animation_Left[2].Next_Rect_Num = 3;

	move_animation_Left[3].m_Rect_Num = 3;
	move_animation_Left[3].m_RectX = 1.0f;
	move_animation_Left[3].m_RectY = 0.0f;
	move_animation_Left[3].m_Rect_Height = 256.0f;
	move_animation_Left[3].m_Rect_Width = 256.0f;
	move_animation_Left[3].m_Display_Flame = 6;
	move_animation_Left[3].Next_Rect_Num = 4;

	move_animation_Left[4].m_Rect_Num = 4;
	move_animation_Left[4].m_RectX = 0.25f;
	move_animation_Left[4].m_RectY = 0.25f;
	move_animation_Left[4].m_Rect_Height = 256.0f;
	move_animation_Left[4].m_Rect_Width = 256.0f;
	move_animation_Left[4].m_Display_Flame = 6;
	move_animation_Left[4].Next_Rect_Num = 5;

	move_animation_Left[5].m_Rect_Num = 5;
	move_animation_Left[5].m_RectX = 0.5f;
	move_animation_Left[5].m_RectY = 0.25f;
	move_animation_Left[5].m_Rect_Height = 256.0f;
	move_animation_Left[5].m_Rect_Width = 256.0f;
	move_animation_Left[5].m_Display_Flame = 6;
	move_animation_Left[5].Next_Rect_Num = 6;

	move_animation_Left[6].m_Rect_Num = 6;
	move_animation_Left[6].m_RectX = 0.75f;
	move_animation_Left[6].m_RectY = 0.25f;
	move_animation_Left[6].m_Rect_Height = 256.0f;
	move_animation_Left[6].m_Rect_Width = 256.0f;
	move_animation_Left[6].m_Display_Flame = 6;
	move_animation_Left[6].Next_Rect_Num = 7;

	move_animation_Left[7].m_Rect_Num = 7;
	move_animation_Left[7].m_RectX = 1.0f;
	move_animation_Left[7].m_RectY = 0.25f;
	move_animation_Left[7].m_Rect_Height = 256.0f;
	move_animation_Left[7].m_Rect_Width = 256.0f;
	move_animation_Left[7].m_Display_Flame = 6;
	move_animation_Left[7].Next_Rect_Num = 8;

	move_animation_Left[8].m_Rect_Num = 8;
	move_animation_Left[8].m_RectX = 0.25f;
	move_animation_Left[8].m_RectY = 0.5f;
	move_animation_Left[8].m_Rect_Height = 256.0f;
	move_animation_Left[8].m_Rect_Width = 256.0f;
	move_animation_Left[8].m_Display_Flame = 6;
	move_animation_Left[8].Next_Rect_Num = 9;

	move_animation_Left[9].m_Rect_Num = 9;
	move_animation_Left[9].m_RectX = 0.5f;
	move_animation_Left[9].m_RectY = 0.5f;
	move_animation_Left[9].m_Rect_Height = 256.0f;
	move_animation_Left[9].m_Rect_Width = 256.0f;
	move_animation_Left[9].m_Display_Flame = 6;
	move_animation_Left[9].Next_Rect_Num = 10;

	move_animation_Left[10].m_Rect_Num = 10;
	move_animation_Left[10].m_RectX = 0.75f;
	move_animation_Left[10].m_RectY = 0.5f;
	move_animation_Left[10].m_Rect_Height = 256.0f;
	move_animation_Left[10].m_Rect_Width = 256.0f;
	move_animation_Left[10].m_Display_Flame = 6;
	move_animation_Left[10].Next_Rect_Num = 0;
}
void TrpPlayer::InitThinkAnimation()
{
	move_animation_Right[0].m_Rect_Num = 0;
	move_animation_Right[0].m_RectX = 0.25f;
	move_animation_Right[0].m_RectY = 0.0f;
	move_animation_Right[0].m_Rect_Height = 256.0f;
	move_animation_Right[0].m_Rect_Width = 256.0f;
	move_animation_Right[0].m_Display_Flame = 6;
	move_animation_Right[0].Next_Rect_Num = 1;

	move_animation_Right[1].m_Rect_Num = 1;
	move_animation_Right[1].m_RectX = 0.5f;
	move_animation_Right[1].m_RectY = 0.0f;
	move_animation_Right[1].m_Rect_Height = 256.0f;
	move_animation_Right[1].m_Rect_Width = 256.0f;
	move_animation_Right[1].m_Display_Flame = 6;
	move_animation_Right[1].Next_Rect_Num = 2;

	move_animation_Right[2].m_Rect_Num = 2;
	move_animation_Right[2].m_RectX = 0.75f;
	move_animation_Right[2].m_RectY = 0.0f;
	move_animation_Right[2].m_Rect_Height = 256.0f;
	move_animation_Right[2].m_Rect_Width = 256.0f;
	move_animation_Right[2].m_Display_Flame = 6;
	move_animation_Right[2].Next_Rect_Num = 3;

	move_animation_Right[3].m_Rect_Num = 3;
	move_animation_Right[3].m_RectX = 1.0f;
	move_animation_Right[3].m_RectY = 0.0f;
	move_animation_Right[3].m_Rect_Height = 256.0f;
	move_animation_Right[3].m_Rect_Width = 256.0f;
	move_animation_Right[3].m_Display_Flame = 6;
	move_animation_Right[3].Next_Rect_Num = 4;

	wait_animation_Right[4].m_Rect_Num = 4;
	wait_animation_Right[4].m_RectX = 0.25f;
	wait_animation_Right[4].m_RectY = 0.25f;
	wait_animation_Right[4].m_Rect_Height = 256.0f;
	wait_animation_Right[4].m_Rect_Width = 256.0f;
	wait_animation_Right[4].m_Display_Flame = 6;
	wait_animation_Right[4].Next_Rect_Num = 5;

	move_animation_Right[5].m_Rect_Num = 5;
	move_animation_Right[5].m_RectX = 0.5f;
	move_animation_Right[5].m_RectY = 0.25f;
	move_animation_Right[5].m_Rect_Height = 256.0f;
	move_animation_Right[5].m_Rect_Width = 256.0f;
	move_animation_Right[5].m_Display_Flame = 6;
	move_animation_Right[5].Next_Rect_Num = 6;

	move_animation_Right[6].m_Rect_Num = 6;
	move_animation_Right[6].m_RectX = 0.75f;
	move_animation_Right[6].m_RectY = 0.25f;
	move_animation_Right[6].m_Rect_Height = 256.0f;
	move_animation_Right[6].m_Rect_Width = 256.0f;
	move_animation_Right[6].m_Display_Flame = 6;
	move_animation_Right[6].Next_Rect_Num = 7;

	move_animation_Right[7].m_Rect_Num = 7;
	move_animation_Right[7].m_RectX = 1.0f;
	move_animation_Right[7].m_RectY = 0.25f;
	move_animation_Right[7].m_Rect_Height = 256.0f;
	move_animation_Right[7].m_Rect_Width = 256.0f;
	move_animation_Right[7].m_Display_Flame = 6;
	move_animation_Right[7].Next_Rect_Num = 8;

	move_animation_Right[8].m_Rect_Num = 8;
	move_animation_Right[8].m_RectX = 0.25f;
	move_animation_Right[8].m_RectY = 0.5f;
	move_animation_Right[8].m_Rect_Height = 256.0f;
	move_animation_Right[8].m_Rect_Width = 256.0f;
	move_animation_Right[8].m_Display_Flame = 6;
	move_animation_Right[8].Next_Rect_Num = 9;

	move_animation_Right[9].m_Rect_Num = 9;
	move_animation_Right[9].m_RectX = 0.5f;
	move_animation_Right[9].m_RectY = 0.5f;
	move_animation_Right[9].m_Rect_Height = 256.0f;
	move_animation_Right[9].m_Rect_Width = 256.0f;
	move_animation_Right[9].m_Display_Flame = 6;
	move_animation_Right[9].Next_Rect_Num = 10;

	move_animation_Right[10].m_Rect_Num = 10;
	move_animation_Right[10].m_RectX = 0.75f;
	move_animation_Right[10].m_RectY = 0.5f;
	move_animation_Right[10].m_Rect_Height = 256.0f;
	move_animation_Right[10].m_Rect_Width = 256.0f;
	move_animation_Right[10].m_Display_Flame = 6;
	move_animation_Right[10].Next_Rect_Num = 0;


	move_animation_Left[0].m_Rect_Num = 0;
	move_animation_Left[0].m_RectX = 0.25f;
	move_animation_Left[0].m_RectY = 0.0f;
	move_animation_Left[0].m_Rect_Height = 256.0f;
	move_animation_Left[0].m_Rect_Width = 256.0f;
	move_animation_Left[0].m_Display_Flame = 6;
	move_animation_Left[0].Next_Rect_Num = 1;

	move_animation_Left[1].m_Rect_Num = 1;
	move_animation_Left[1].m_RectX = 0.5f;
	move_animation_Left[1].m_RectY = 0.0f;
	move_animation_Left[1].m_Rect_Height = 256.0f;
	move_animation_Left[1].m_Rect_Width = 256.0f;
	move_animation_Left[1].m_Display_Flame = 6;
	move_animation_Left[1].Next_Rect_Num = 2;

	move_animation_Left[2].m_Rect_Num = 2;
	move_animation_Left[2].m_RectX = 0.75f;
	move_animation_Left[2].m_RectY = 0.0f;
	move_animation_Left[2].m_Rect_Height = 256.0f;
	move_animation_Left[2].m_Rect_Width = 256.0f;
	move_animation_Left[2].m_Display_Flame = 6;
	move_animation_Left[2].Next_Rect_Num = 3;

	move_animation_Left[3].m_Rect_Num = 3;
	move_animation_Left[3].m_RectX = 1.0f;
	move_animation_Left[3].m_RectY = 0.0f;
	move_animation_Left[3].m_Rect_Height = 256.0f;
	move_animation_Left[3].m_Rect_Width = 256.0f;
	move_animation_Left[3].m_Display_Flame = 6;
	move_animation_Left[3].Next_Rect_Num = 4;

	move_animation_Left[4].m_Rect_Num = 4;
	move_animation_Left[4].m_RectX = 0.25f;
	move_animation_Left[4].m_RectY = 0.25f;
	move_animation_Left[4].m_Rect_Height = 256.0f;
	move_animation_Left[4].m_Rect_Width = 256.0f;
	move_animation_Left[4].m_Display_Flame = 6;
	move_animation_Left[4].Next_Rect_Num = 5;

	move_animation_Left[5].m_Rect_Num = 5;
	move_animation_Left[5].m_RectX = 0.5f;
	move_animation_Left[5].m_RectY = 0.25f;
	move_animation_Left[5].m_Rect_Height = 256.0f;
	move_animation_Left[5].m_Rect_Width = 256.0f;
	move_animation_Left[5].m_Display_Flame = 6;
	move_animation_Left[5].Next_Rect_Num = 6;

	move_animation_Left[6].m_Rect_Num = 6;
	move_animation_Left[6].m_RectX = 0.75f;
	move_animation_Left[6].m_RectY = 0.25f;
	move_animation_Left[6].m_Rect_Height = 256.0f;
	move_animation_Left[6].m_Rect_Width = 256.0f;
	move_animation_Left[6].m_Display_Flame = 6;
	move_animation_Left[6].Next_Rect_Num = 7;

	move_animation_Left[7].m_Rect_Num = 7;
	move_animation_Left[7].m_RectX = 1.0f;
	move_animation_Left[7].m_RectY = 0.25f;
	move_animation_Left[7].m_Rect_Height = 256.0f;
	move_animation_Left[7].m_Rect_Width = 256.0f;
	move_animation_Left[7].m_Display_Flame = 6;
	move_animation_Left[7].Next_Rect_Num = 8;

	move_animation_Left[8].m_Rect_Num = 8;
	move_animation_Left[8].m_RectX = 0.25f;
	move_animation_Left[8].m_RectY = 0.5f;
	move_animation_Left[8].m_Rect_Height = 256.0f;
	move_animation_Left[8].m_Rect_Width = 256.0f;
	move_animation_Left[8].m_Display_Flame = 6;
	move_animation_Left[8].Next_Rect_Num = 9;

	move_animation_Left[9].m_Rect_Num = 9;
	move_animation_Left[9].m_RectX = 0.5f;
	move_animation_Left[9].m_RectY = 0.5f;
	move_animation_Left[9].m_Rect_Height = 256.0f;
	move_animation_Left[9].m_Rect_Width = 256.0f;
	move_animation_Left[9].m_Display_Flame = 6;
	move_animation_Left[9].Next_Rect_Num = 10;

	move_animation_Left[10].m_Rect_Num = 10;
	move_animation_Left[10].m_RectX = 0.75f;
	move_animation_Left[10].m_RectY = 0.5f;
	move_animation_Left[10].m_Rect_Height = 256.0f;
	move_animation_Left[10].m_Rect_Width = 256.0f;
	move_animation_Left[10].m_Display_Flame = 6;
	move_animation_Left[10].Next_Rect_Num = 0;
}
void TrpPlayer::InitDeathAnimation()
{
	move_animation_Right[0].m_Rect_Num = 0;
	move_animation_Right[0].m_RectX = 0.25f;
	move_animation_Right[0].m_RectY = 0.0f;
	move_animation_Right[0].m_Rect_Height = 256.0f;
	move_animation_Right[0].m_Rect_Width = 256.0f;
	move_animation_Right[0].m_Display_Flame = 6;
	move_animation_Right[0].Next_Rect_Num = 1;

	move_animation_Right[1].m_Rect_Num = 1;
	move_animation_Right[1].m_RectX = 0.5f;
	move_animation_Right[1].m_RectY = 0.0f;
	move_animation_Right[1].m_Rect_Height = 256.0f;
	move_animation_Right[1].m_Rect_Width = 256.0f;
	move_animation_Right[1].m_Display_Flame = 6;
	move_animation_Right[1].Next_Rect_Num = 2;

	move_animation_Right[2].m_Rect_Num = 2;
	move_animation_Right[2].m_RectX = 0.75f;
	move_animation_Right[2].m_RectY = 0.0f;
	move_animation_Right[2].m_Rect_Height = 256.0f;
	move_animation_Right[2].m_Rect_Width = 256.0f;
	move_animation_Right[2].m_Display_Flame = 6;
	move_animation_Right[2].Next_Rect_Num = 3;

	move_animation_Right[3].m_Rect_Num = 3;
	move_animation_Right[3].m_RectX = 1.0f;
	move_animation_Right[3].m_RectY = 0.0f;
	move_animation_Right[3].m_Rect_Height = 256.0f;
	move_animation_Right[3].m_Rect_Width = 256.0f;
	move_animation_Right[3].m_Display_Flame = 6;
	move_animation_Right[3].Next_Rect_Num = 4;

	wait_animation_Right[4].m_Rect_Num = 4;
	wait_animation_Right[4].m_RectX = 0.25f;
	wait_animation_Right[4].m_RectY = 0.25f;
	wait_animation_Right[4].m_Rect_Height = 256.0f;
	wait_animation_Right[4].m_Rect_Width = 256.0f;
	wait_animation_Right[4].m_Display_Flame = 6;
	wait_animation_Right[4].Next_Rect_Num = 5;

	move_animation_Right[5].m_Rect_Num = 5;
	move_animation_Right[5].m_RectX = 0.5f;
	move_animation_Right[5].m_RectY = 0.25f;
	move_animation_Right[5].m_Rect_Height = 256.0f;
	move_animation_Right[5].m_Rect_Width = 256.0f;
	move_animation_Right[5].m_Display_Flame = 6;
	move_animation_Right[5].Next_Rect_Num = 6;

	move_animation_Right[6].m_Rect_Num = 6;
	move_animation_Right[6].m_RectX = 0.75f;
	move_animation_Right[6].m_RectY = 0.25f;
	move_animation_Right[6].m_Rect_Height = 256.0f;
	move_animation_Right[6].m_Rect_Width = 256.0f;
	move_animation_Right[6].m_Display_Flame = 6;
	move_animation_Right[6].Next_Rect_Num = 7;

	move_animation_Right[7].m_Rect_Num = 7;
	move_animation_Right[7].m_RectX = 1.0f;
	move_animation_Right[7].m_RectY = 0.25f;
	move_animation_Right[7].m_Rect_Height = 256.0f;
	move_animation_Right[7].m_Rect_Width = 256.0f;
	move_animation_Right[7].m_Display_Flame = 6;
	move_animation_Right[7].Next_Rect_Num = 8;

	move_animation_Right[8].m_Rect_Num = 8;
	move_animation_Right[8].m_RectX = 0.25f;
	move_animation_Right[8].m_RectY = 0.5f;
	move_animation_Right[8].m_Rect_Height = 256.0f;
	move_animation_Right[8].m_Rect_Width = 256.0f;
	move_animation_Right[8].m_Display_Flame = 6;
	move_animation_Right[8].Next_Rect_Num = 9;

	move_animation_Right[9].m_Rect_Num = 9;
	move_animation_Right[9].m_RectX = 0.5f;
	move_animation_Right[9].m_RectY = 0.5f;
	move_animation_Right[9].m_Rect_Height = 256.0f;
	move_animation_Right[9].m_Rect_Width = 256.0f;
	move_animation_Right[9].m_Display_Flame = 6;
	move_animation_Right[9].Next_Rect_Num = 10;

	move_animation_Right[10].m_Rect_Num = 10;
	move_animation_Right[10].m_RectX = 0.75f;
	move_animation_Right[10].m_RectY = 0.5f;
	move_animation_Right[10].m_Rect_Height = 256.0f;
	move_animation_Right[10].m_Rect_Width = 256.0f;
	move_animation_Right[10].m_Display_Flame = 6;
	move_animation_Right[10].Next_Rect_Num = 0;


	move_animation_Left[0].m_Rect_Num = 0;
	move_animation_Left[0].m_RectX = 0.25f;
	move_animation_Left[0].m_RectY = 0.0f;
	move_animation_Left[0].m_Rect_Height = 256.0f;
	move_animation_Left[0].m_Rect_Width = 256.0f;
	move_animation_Left[0].m_Display_Flame = 6;
	move_animation_Left[0].Next_Rect_Num = 1;

	move_animation_Left[1].m_Rect_Num = 1;
	move_animation_Left[1].m_RectX = 0.5f;
	move_animation_Left[1].m_RectY = 0.0f;
	move_animation_Left[1].m_Rect_Height = 256.0f;
	move_animation_Left[1].m_Rect_Width = 256.0f;
	move_animation_Left[1].m_Display_Flame = 6;
	move_animation_Left[1].Next_Rect_Num = 2;

	move_animation_Left[2].m_Rect_Num = 2;
	move_animation_Left[2].m_RectX = 0.75f;
	move_animation_Left[2].m_RectY = 0.0f;
	move_animation_Left[2].m_Rect_Height = 256.0f;
	move_animation_Left[2].m_Rect_Width = 256.0f;
	move_animation_Left[2].m_Display_Flame = 6;
	move_animation_Left[2].Next_Rect_Num = 3;

	move_animation_Left[3].m_Rect_Num = 3;
	move_animation_Left[3].m_RectX = 1.0f;
	move_animation_Left[3].m_RectY = 0.0f;
	move_animation_Left[3].m_Rect_Height = 256.0f;
	move_animation_Left[3].m_Rect_Width = 256.0f;
	move_animation_Left[3].m_Display_Flame = 6;
	move_animation_Left[3].Next_Rect_Num = 4;

	move_animation_Left[4].m_Rect_Num = 4;
	move_animation_Left[4].m_RectX = 0.25f;
	move_animation_Left[4].m_RectY = 0.25f;
	move_animation_Left[4].m_Rect_Height = 256.0f;
	move_animation_Left[4].m_Rect_Width = 256.0f;
	move_animation_Left[4].m_Display_Flame = 6;
	move_animation_Left[4].Next_Rect_Num = 5;

	move_animation_Left[5].m_Rect_Num = 5;
	move_animation_Left[5].m_RectX = 0.5f;
	move_animation_Left[5].m_RectY = 0.25f;
	move_animation_Left[5].m_Rect_Height = 256.0f;
	move_animation_Left[5].m_Rect_Width = 256.0f;
	move_animation_Left[5].m_Display_Flame = 6;
	move_animation_Left[5].Next_Rect_Num = 6;

	move_animation_Left[6].m_Rect_Num = 6;
	move_animation_Left[6].m_RectX = 0.75f;
	move_animation_Left[6].m_RectY = 0.25f;
	move_animation_Left[6].m_Rect_Height = 256.0f;
	move_animation_Left[6].m_Rect_Width = 256.0f;
	move_animation_Left[6].m_Display_Flame = 6;
	move_animation_Left[6].Next_Rect_Num = 7;

	move_animation_Left[7].m_Rect_Num = 7;
	move_animation_Left[7].m_RectX = 1.0f;
	move_animation_Left[7].m_RectY = 0.25f;
	move_animation_Left[7].m_Rect_Height = 256.0f;
	move_animation_Left[7].m_Rect_Width = 256.0f;
	move_animation_Left[7].m_Display_Flame = 6;
	move_animation_Left[7].Next_Rect_Num = 8;

	move_animation_Left[8].m_Rect_Num = 8;
	move_animation_Left[8].m_RectX = 0.25f;
	move_animation_Left[8].m_RectY = 0.5f;
	move_animation_Left[8].m_Rect_Height = 256.0f;
	move_animation_Left[8].m_Rect_Width = 256.0f;
	move_animation_Left[8].m_Display_Flame = 6;
	move_animation_Left[8].Next_Rect_Num = 9;

	move_animation_Left[9].m_Rect_Num = 9;
	move_animation_Left[9].m_RectX = 0.5f;
	move_animation_Left[9].m_RectY = 0.5f;
	move_animation_Left[9].m_Rect_Height = 256.0f;
	move_animation_Left[9].m_Rect_Width = 256.0f;
	move_animation_Left[9].m_Display_Flame = 6;
	move_animation_Left[9].Next_Rect_Num = 10;

	move_animation_Left[10].m_Rect_Num = 10;
	move_animation_Left[10].m_RectX = 0.75f;
	move_animation_Left[10].m_RectY = 0.5f;
	move_animation_Left[10].m_Rect_Height = 256.0f;
	move_animation_Left[10].m_Rect_Width = 256.0f;
	move_animation_Left[10].m_Display_Flame = 6;
	move_animation_Left[10].Next_Rect_Num = 0;
}

void TrpPlayer::MoveAnimation()
{

}
void TrpPlayer::JumpAnimation()
{

}
void TrpPlayer::ThinkAnimation()
{

}
void TrpPlayer::DeathAnimation()
{

}

void TrpPlayer::InitClearAnimation()
{

}

void TrpPlayer::ClearAnimation()
{

}

void TrpPlayer::InitDamageAnimation()
{

}

void TrpPlayer::DamageAnimation()
{

}