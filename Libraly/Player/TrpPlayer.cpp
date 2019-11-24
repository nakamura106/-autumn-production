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
	//InitAnimation();
	InitMoveAnimation();
}

void TrpPlayer::Load()
{
	LoadTexture("Res/Tex/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_Attack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_Attack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Damage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_Damage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Jump_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_Jump_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_Tp_RightTex);
	LoadTexture("Res/Tex/Player_JumpAttack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_JumpAttack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_Tp_RightTex);
	LoadTexture("Res/Tex/Player_JumpDamage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_JumpDamage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_Tp_RightTex);
	LoadTexture("Res/Tex/Player_Walk_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_Tp_LeftTex);
	LoadTexture("Res/Tex/Player_Walk_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_Tp_RightTex);

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
		switch (m_state)
		{
		case (int)P_State::Wait:
			//WaitAnimation();
			MoveAnimation();
			break;
		case(int)P_State::Move:
			MoveAnimation();
			break;
		case(int)P_State::Jump:
			JumpAnimation();
			break;
		case(int)P_State::Jump_Attack:
			JumpAttackAnimation();
			break;
		case(int)P_State::Jump_Damage:
			JumpDamageAnimation();
			break;
		case(int)P_State::Damage:
			DamageAnimation();
			break;
		case(int)P_State::Attack:
			AttackAnimation();
			break;
		default:
			break;
		}
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
	else
	{
		m_state = (int)P_State::Wait;
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
	InitMoveAnimation();
	InitAttackAnimation();
	InitJumpAttackAnimation();
	InitJumpAnimation();
	InitThinkAnimation();
	InitDeathAnimation();
	InitClearAnimation();
	InitDamageAnimation();
	InitJumpDamageAnimation();
	InitOpeningAnimation();
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

void TrpPlayer::InitMoveAnimation()
{
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{
		
		move_animation_Right[i].m_RectX = R_X;
		move_animation_Right[i].m_RectY = R_Y;
		move_animation_Right[i].m_Rect_Height = Rect_Height;
		move_animation_Right[i].m_Rect_Width = Rect_Width;
		move_animation_Right[i].m_Display_Flame = Dispflame;
		

		
		move_animation_Left[i].m_RectX = R_X;
		move_animation_Left[i].m_RectY = R_Y;
		move_animation_Left[i].m_Rect_Height = Rect_Height;
		move_animation_Left[i].m_Rect_Width = Rect_Width;
		move_animation_Left[i].m_Display_Flame = Dispflame;
		
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

void TrpPlayer::InitAttackAnimation()
{
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{

		attack_animation_Right[i].m_RectX = R_X;
		attack_animation_Right[i].m_RectY = R_Y;
		attack_animation_Right[i].m_Rect_Height = Rect_Height;
		attack_animation_Right[i].m_Rect_Width = Rect_Width;
		attack_animation_Right[i].m_Display_Flame = Dispflame;



		attack_animation_Left[i].m_RectX = R_X;
		attack_animation_Left[i].m_RectY = R_Y;
		attack_animation_Left[i].m_Rect_Height = Rect_Height;
		attack_animation_Left[i].m_Rect_Width = Rect_Width;
		attack_animation_Left[i].m_Display_Flame = Dispflame;

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

void TrpPlayer::InitJumpAttackAnimation()
{
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{

		jump_attack_animation_Right[i].m_RectX = R_X;
		jump_attack_animation_Right[i].m_RectY = R_Y;
		jump_attack_animation_Right[i].m_Rect_Height = Rect_Height;
		jump_attack_animation_Right[i].m_Rect_Width = Rect_Width;
		jump_attack_animation_Right[i].m_Display_Flame = Dispflame;



		jump_attack_animation_Left[i].m_RectX = R_X;
		jump_attack_animation_Left[i].m_RectY = R_Y;
		jump_attack_animation_Left[i].m_Rect_Height = Rect_Height;
		jump_attack_animation_Left[i].m_Rect_Width = Rect_Width;
		jump_attack_animation_Left[i].m_Display_Flame = Dispflame;

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
	static float R_X = 0, R_Y = 0;

	for (int i = 0; i <= 11; i++)
	{
		
		jump_animation_Right[i].m_RectX = R_X;
		jump_animation_Right[i].m_RectY = R_Y;
		jump_animation_Right[i].m_Rect_Height = Rect_Height;
		jump_animation_Right[i].m_Rect_Width = Rect_Width;
		jump_animation_Right[i].m_Display_Flame = Dispflame;
		

		
		jump_animation_Left[i].m_RectX = R_X;
		jump_animation_Left[i].m_RectY = R_Y;
		jump_animation_Left[i].m_Rect_Height = Rect_Height;
		jump_animation_Left[i].m_Rect_Width = Rect_Width;
		jump_animation_Left[i].m_Display_Flame = Dispflame;
		
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



void TrpPlayer::InitThinkAnimation()
{
	static float R_X = 0, R_Y = 0;

	for (int i = 0; i <= 11; i++)
	{
		think_animation_Right[i].m_RectX = R_X;
		think_animation_Right[i].m_RectY = R_Y;
		think_animation_Right[i].m_Rect_Height = Rect_Height;
		think_animation_Right[i].m_Rect_Width = Rect_Width;
		think_animation_Right[i].m_Display_Flame = Dispflame;
		


		
		think_animation_Left[i].m_RectX = R_X;
		think_animation_Left[i].m_RectY = R_Y;
		think_animation_Left[i].m_Rect_Height = Rect_Height;
		think_animation_Left[i].m_Rect_Width = Rect_Width;
		think_animation_Left[i].m_Display_Flame = Dispflame;
		
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

void TrpPlayer::InitDamageAnimation()
{
	static float R_X = 0, R_Y = 0;

	for (int i = 0; i <= 11; i++)
	{
		damage_animation_Right[i].m_RectX = R_X;
		damage_animation_Right[i].m_RectY = R_Y;
		damage_animation_Right[i].m_Rect_Height = Rect_Height;
		damage_animation_Right[i].m_Rect_Width = Rect_Width;
		damage_animation_Right[i].m_Display_Flame = Dispflame;




		damage_animation_Left[i].m_RectX = R_X;
		damage_animation_Left[i].m_RectY = R_Y;
		damage_animation_Left[i].m_Rect_Height = Rect_Height;
		damage_animation_Left[i].m_Rect_Width = Rect_Width;
		damage_animation_Left[i].m_Display_Flame = Dispflame;

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

void TrpPlayer::InitJumpDamageAnimation()
{

}

void TrpPlayer::InitDeathAnimation()
{
	static float R_X = 0, R_Y = 0;

	for (int i = 0; i <= 11; i++)
	{
		death_animation_Right[i].m_RectX = R_X;
		death_animation_Right[i].m_RectY = R_Y;
		death_animation_Right[i].m_Rect_Height = Rect_Height;
		death_animation_Right[i].m_Rect_Width = Rect_Width;
		death_animation_Right[i].m_Display_Flame = Dispflame;




		death_animation_Left[i].m_RectX = R_X;
		death_animation_Left[i].m_RectY = R_Y;
		death_animation_Left[i].m_Rect_Height = Rect_Height;
		death_animation_Left[i].m_Rect_Width = Rect_Width;
		death_animation_Left[i].m_Display_Flame = Dispflame;

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

void TrpPlayer::InitClearAnimation()
{
	static float R_X = 0, R_Y = 0;

	for (int i = 0; i <= 11; i++)
	{
		clear_animation_Right[i].m_RectX = R_X;
		clear_animation_Right[i].m_RectY = R_Y;
		clear_animation_Right[i].m_Rect_Height = Rect_Height;
		clear_animation_Right[i].m_Rect_Width = Rect_Width;
		clear_animation_Right[i].m_Display_Flame = Dispflame;




		clear_animation_Left[i].m_RectX = R_X;
		clear_animation_Left[i].m_RectY = R_Y;
		clear_animation_Left[i].m_Rect_Height = Rect_Height;
		clear_animation_Left[i].m_Rect_Width = Rect_Width;
		clear_animation_Left[i].m_Display_Flame = Dispflame;

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

void TrpPlayer::InitOpeningAnimation()
{
	static float R_X = 0, R_Y = 0;
	for (int i = 0; i <= 11; i++)
	{

		opening_animation[i].m_RectX = R_X;
		opening_animation[i].m_RectY = R_Y;
		opening_animation[i].m_Rect_Height = Rect_Height;
		opening_animation[i].m_Rect_Width = Rect_Width;
		opening_animation[i].m_Display_Flame = Dispflame;

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
		DrawUVTexture(m_pos.x - 128, m_pos.y, wait_animation_Left[j].m_Rect_Width, wait_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_LeftTex), wait_animation_Left[j].m_RectX, wait_animation_Left[j].m_RectY);
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

void TrpPlayer::MoveAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, move_animation_Right[i].m_Rect_Width, move_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Walk_Tp_RightTex), move_animation_Right[i].m_RectX, move_animation_Right[i].m_RectY);
		move_animation_Right[i].m_Display_Flame--;
		if (move_animation_Right[i].m_Display_Flame <= 0)
		{
			move_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, move_animation_Left[j].m_Rect_Width, move_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Walk_Tp_LeftTex), move_animation_Left[j].m_RectX, move_animation_Left[j].m_RectY);
		move_animation_Left[j].m_Display_Flame--;
		if (move_animation_Left[j].m_Display_Flame <= 0)
		{
			move_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::AttackAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, attack_animation_Right[i].m_Rect_Width, attack_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Attack_Tp_RightTex), attack_animation_Right[i].m_RectX, attack_animation_Right[i].m_RectY);
		attack_animation_Right[i].m_Display_Flame--;
		if (attack_animation_Right[i].m_Display_Flame <= 0)
		{
			attack_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
				m_state = (int)P_State::Wait;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, attack_animation_Left[j].m_Rect_Width, attack_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Attack_Tp_LeftTex), attack_animation_Left[j].m_RectX, attack_animation_Left[j].m_RectY);
		attack_animation_Left[j].m_Display_Flame--;
		if (attack_animation_Left[j].m_Display_Flame <= 0)
		{
			attack_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
				m_state = (int)P_State::Wait;
			}

		}
	}
}

void TrpPlayer::JumpAttackAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, jump_attack_animation_Right[i].m_Rect_Width, jump_attack_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_JumpAttack_Tp_RightTex), jump_attack_animation_Right[i].m_RectX, jump_attack_animation_Right[i].m_RectY);
		jump_attack_animation_Right[i].m_Display_Flame--;
		if (jump_attack_animation_Right[i].m_Display_Flame <= 0)
		{
			jump_attack_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, move_animation_Left[j].m_Rect_Width, move_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_JumpAttack_Tp_LeftTex), jump_attack_animation_Left[j].m_RectX, jump_attack_animation_Left[j].m_RectY);
		jump_attack_animation_Left[j].m_Display_Flame--;
		if (jump_attack_animation_Left[j].m_Display_Flame <= 0)
		{
			jump_attack_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}
}

void TrpPlayer::JumpAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, jump_animation_Right[i].m_Rect_Width, jump_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Jump_Tp_RightTex), jump_animation_Right[i].m_RectX, jump_animation_Right[i].m_RectY);
		jump_animation_Right[i].m_Display_Flame--;
		if (jump_animation_Right[i].m_Display_Flame <= 0)
		{
			jump_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, jump_animation_Left[j].m_Rect_Width, jump_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Jump_Tp_LeftTex), jump_animation_Left[j].m_RectX, jump_animation_Left[j].m_RectY);
		jump_animation_Left[j].m_Display_Flame--;
		if (jump_animation_Left[j].m_Display_Flame <= 0)
		{
			jump_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::ThinkAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, think_animation_Right[i].m_Rect_Width, think_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_RightTex), think_animation_Right[i].m_RectX, think_animation_Right[i].m_RectY);
		think_animation_Right[i].m_Display_Flame--;
		if (think_animation_Right[i].m_Display_Flame <= 0)
		{
			think_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, think_animation_Left[j].m_Rect_Width, think_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_LeftTex), think_animation_Left[j].m_RectX, think_animation_Left[j].m_RectY);
		think_animation_Left[j].m_Display_Flame--;
		if (think_animation_Left[j].m_Display_Flame <= 0)
		{
			think_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::DeathAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, death_animation_Right[i].m_Rect_Width, death_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_RightTex), death_animation_Right[i].m_RectX, death_animation_Right[i].m_RectY);
		death_animation_Right[i].m_Display_Flame--;
		if (death_animation_Right[i].m_Display_Flame <= 0)
		{
			death_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, death_animation_Left[j].m_Rect_Width, death_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Taiki_Tp_LeftTex), death_animation_Left[j].m_RectX, death_animation_Left[j].m_RectY);
		death_animation_Left[j].m_Display_Flame--;
		if (death_animation_Left[j].m_Display_Flame <= 0)
		{
			death_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::ClearAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, clear_animation_Right[i].m_Rect_Width, clear_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Clear_Tp_RightTex), clear_animation_Right[i].m_RectX, clear_animation_Right[i].m_RectY);
		clear_animation_Right[i].m_Display_Flame--;
		if (clear_animation_Right[i].m_Display_Flame <= 0)
		{
			clear_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, clear_animation_Left[j].m_Rect_Width, clear_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Clear_Tp_LeftTex), clear_animation_Left[j].m_RectX, clear_animation_Left[j].m_RectY);
		clear_animation_Left[j].m_Display_Flame--;
		if (clear_animation_Left[j].m_Display_Flame <= 0)
		{
			clear_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::DamageAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, damage_animation_Right[i].m_Rect_Width, damage_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Damage_Tp_RightTex), damage_animation_Right[i].m_RectX, damage_animation_Right[i].m_RectY);
		damage_animation_Right[i].m_Display_Flame--;
		if (damage_animation_Right[i].m_Display_Flame <= 0)
		{
			damage_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, damage_animation_Left[j].m_Rect_Width, damage_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_Damage_Tp_LeftTex), damage_animation_Left[j].m_RectX, damage_animation_Left[j].m_RectY);
		damage_animation_Left[j].m_Display_Flame--;
		if (damage_animation_Left[j].m_Display_Flame <= 0)
		{
			damage_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::JumpDamageAnimation()
{
	static int i = 0;
	static int j = 0;
	if (m_direction == Right)
	{
		DrawUVTexture(m_pos.x, m_pos.y, jump_damage_animation_Right[i].m_Rect_Width, jump_damage_animation_Right[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_JumpDamage_Tp_RightTex), jump_damage_animation_Right[i].m_RectX, jump_damage_animation_Right[i].m_RectY);
		jump_damage_animation_Right[i].m_Display_Flame--;
		if (jump_damage_animation_Right[i].m_Display_Flame <= 0)
		{
			jump_damage_animation_Right[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	}
	if (m_direction == Left)
	{
		DrawUVTexture(m_pos.x - 128, m_pos.y, jump_damage_animation_Left[j].m_Rect_Width, jump_damage_animation_Left[j].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_JumpDamage_Tp_LeftTex), jump_damage_animation_Left[j].m_RectX, jump_damage_animation_Left[j].m_RectY);
		jump_damage_animation_Left[j].m_Display_Flame--;
		if (damage_animation_Left[j].m_Display_Flame <= 0)
		{
			jump_damage_animation_Left[j].m_Display_Flame = Dispflame;

			j++;
			if (j >= 11)
			{
				j = 0;
			}

		}
	}

}

void TrpPlayer::OpeningAnimation()
{
	static int i = 0;
	static int j = 0;
	
		DrawUVTexture(m_pos.x, m_pos.y, opening_animation[i].m_Rect_Width, opening_animation[i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, GamePlayer_OpeningTex), opening_animation[i].m_RectX, opening_animation[i].m_RectY);
		opening_animation[i].m_Display_Flame--;
		if (opening_animation[i].m_Display_Flame <= 0)
		{
			opening_animation[i].m_Display_Flame = Dispflame;
			i++;
			if (i >= 11)
			{
				i = 0;
			}
		}
	

}