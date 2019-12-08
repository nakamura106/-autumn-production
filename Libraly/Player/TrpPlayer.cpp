#include"TrpPlayer.h"
#include"../Engine/Graphics.h"
//#include"../Texture/Texture.h"
#include"../Object/Definition.h"
#include"../Engine/Vec.h"
#include"../Engine/Input.h"
#include"../Map/Map.h"
#include"../Bullet/PlayerBullet.h"





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
	m_hp = P_MaxHP;
	m_direction = RIGHT;
	m_speed = P_speed;
	m_state = (int)P_State::Wait;
	m_Key = (int)Key::Major;
	m_i = 0;
	m_map_pos = P_posX;
	m_pos.x = P_posX;
	m_pos.y = P_posY;
	m_List = GamePlayer_Taiki_Tp_RightTex;
	for (int i = 0; i < 6; i++)
	{
		m_play_note[i] = false;
	}
	for (int i = 0; i < 3; i++)
	{
		notebox[i] = 0;
	}
	Load();
	InitAnimation();
}

void TrpPlayer::Load()
{
	LoadTexture("Res/Tex/Player/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Attack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Attack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_Damage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Damage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_Jump_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Jump_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_JumpAttack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_JumpAttack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_JumpDamage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_JumpDamage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_Tp_RightTex);
	LoadTexture("Res/Tex/Player/Player_Walk_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_Tp_LeftTex);
	LoadTexture("Res/Tex/Player/Player_Walk_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_Tp_RightTex);
}


void TrpPlayer::Update()
{
	P_Controll();
	UpdateAnimation();
	DrawAnimation();
	/*if (�o���b�g��X��player��range�������珈�����s��)
	{
		ReleaseNote();
	}*/
}

void TrpPlayer::UpdateAnimation()
{
	//�폜���肪false(�폜���������s����Ȃ�)�Ȃ烂�[�V�������Ƃ�Textureid�𑗂�
	if (m_is_delete == false)
	{
		switch (m_state)
		{
		case (int)P_State::Wait:
			GetMotion(GamePlayer_Taiki_Tp_LeftTex, GamePlayer_Taiki_Tp_RightTex);
			break;
		
		case(int)P_State::Move:
			GetMotion(GamePlayer_Walk_Tp_LeftTex, GamePlayer_Walk_Tp_RightTex);
			break;
		
		case(int)P_State::Jump:
			GetMotion(GamePlayer_Jump_Tp_LeftTex, GamePlayer_Jump_Tp_RightTex);
			break;
		
		case(int)P_State::Jump_Attack:
			GetMotion(GamePlayer_JumpAttack_Tp_LeftTex, GamePlayer_JumpAttack_Tp_RightTex);
			break;
		
		case(int)P_State::Jump_Damage:
			GetMotion(GamePlayer_JumpDamage_Tp_LeftTex, GamePlayer_JumpDamage_Tp_RightTex);
			break;
		
		case(int)P_State::Damage:
			GetMotion(GamePlayer_Damage_Tp_LeftTex, GamePlayer_Damage_Tp_RightTex);
			break;
		
		case(int)P_State::Attack:
			GetMotion(GamePlayer_Attack_Tp_LeftTex, GamePlayer_Attack_Tp_RightTex);
			break;
		
		default:
			break;
		}
	}
}

void TrpPlayer::Draw()
{
	DrawUVTexture(m_pos.x, m_pos.y, Animation[m_i].m_Rect_Width, Animation[m_i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, m_List), Animation[m_i].m_RectX, Animation[m_i].m_RectY);
	
	Drawatk();
}

int TrpPlayer::atkjudge()
{
	if (notebox[0] == A&&notebox[1]==A&& notebox[2]==A|| notebox[0] == A && notebox[1] == B && notebox[2] == A &&
		notebox[0 || 1 || 2] != 0)
	{
		if (notebox[1] == A)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	
	if (notebox[0] == B && notebox[1] == B && notebox[2] == B || notebox[0] == B && notebox[1] == A && notebox[2] == B&&
		notebox[0 || 1 || 2] != 0)
	{
		if (notebox[1] == B)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}

	if (notebox[0] == A && notebox[1] == A && notebox[2] == B || notebox[0] == A && notebox[1] == B && notebox[2] == B ||
		notebox[0] == B && notebox[1] == B && notebox[2] == A || notebox[0] == B && notebox[1] == A && notebox[2] == A)
	{
		return 5;
	}
	return 0;
}

void TrpPlayer::Drawatk()
{
	if (notebox[0] == A)
	{
		DrawFont(40, 200, "A", Large, Red);
	}
	if (notebox[0] == B)
	{
		DrawFont(40, 200, "B", Large, Red);
	}
	if (notebox[1] == A)
	{
		DrawFont(80, 200, "A", Large, Red);
	}
	if (notebox[1] == B)
	{
		DrawFont(80, 200, "B", Large, Red);
	}
	if (notebox[2] == A)
	{
		DrawFont(120, 200, "A", Large, Red);
	}
	if (notebox[2] == B)
	{
		DrawFont(120, 200, "B", Large, Red);
	}
	if (atkjudge() == 1)
	{
		DrawFont(180, 200, "AAA�U������", Large, Red);
	}
	if (atkjudge() == 2)
	{
		DrawFont(180, 200, "ABA�U������", Large, Red);
	}
	if (atkjudge() == 3)
	{
		DrawFont(180, 200, "BBB�U������", Large, Red);
	}
	if (atkjudge() == 4)
	{
		DrawFont(180, 200, "BAB�U������", Large, Red);
	}
	if (atkjudge() == 5)
	{
		DrawFont(180, 200, "�U�����s", Large, Red);
	}
}

void TrpPlayer::P_Controll()
{


	/*�{�^���𗣂�����Ƀ��[�V������
	�p�����Ă��܂�Ȃ��悤�ɂ��鏈��*/
	if (m_is_active == true)
	{
		m_is_active = false;
	}
	
	// ���܂Ń{�^������
	
	if (GetKey(A_KEY) == true)
	{
		ReleaseNote();
		 
		 
		//PlayerBullet(m_pos.x, m_pos.y, 10.0f, m_direction);
	}
	
	//�E�ړ�
	if (GetKey(RIGHT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		if (m_direction == LEFT) {
			m_pos.x += lrAdjustment;
		}
		if (m_map_pos <= 3800)
		{
			m_map_pos += m_speed;
		}
		m_direction = RIGHT;
		m_pos.x += m_speed;
		m_is_active = true;
	}

	//���ړ�
	if (GetKey(LEFT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		if (m_direction == RIGHT) {
			m_pos.x -= lrAdjustment;
		}
		if (m_map_pos >= 0)
		{
			m_map_pos -= m_speed;
		}
		if (m_map_pos <= m_pos.x)
		{
			m_pos.x -= m_speed;
		}
		m_direction = LEFT;
		m_is_active = true;
	}

	//�W�����v����
	if (GetKey(SPACE_KEY) == true)
	{
		m_do_jump = true;
		m_is_active = true;
	}

	//�����Z���؂�ւ�����(�����Ă���Ԃ̂�)
	if (GetKey(SHIFT_KEY) == true)
	{
		m_Key = (int)Key::Minor;
	}
	else
	{
		m_Key = (int)Key::Major;
	}


	//��������
	if (GetKey(ONE_KEY) == true)
	{
		if (m_play_note[0] != true&&m_Key == (int)Key::Major)
		{
			m_play_note[0] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					break;
				}
			}
		}
		if (m_play_note[3] != true&& m_Key == (int)Key::Minor)
		{
			m_play_note[3] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = B;
					break;
				}
			}
		}
	}

	//��������
	if (GetKey(TWO_KEY) == true)
	{
		if (m_play_note[1] != true  && m_Key == (int)Key::Major)
		{
			m_play_note[1] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					break;
				}
			}
		}
		if (m_play_note[4] != true && m_Key == (int)Key::Minor)
		{
			m_play_note[4] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = B;
					break;
				}
			}
		}
	}

	//��������
	if (GetKey(THREE_KEY) == true)
	{
		if (m_play_note[2] != true&& m_Key == (int)Key::Major)
		{
			m_play_note[2] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					break;
				}
			}
		}
		if (m_play_note[5] != true&& m_Key == (int)Key::Minor)
		{
			m_play_note[5] = true;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = B;
					break;
				}
			}
		}
	}
	// ��

	//active��false�Ȃ�ҋ@��Ԃɂ��鏈��
	if (m_is_active == false)
	{
		m_state = (int)P_State::Wait;
	}

	//�v���C���[���W�����v���Ă��邩���肷��(���Ă���Ȃ�W�����v�֐����Ăяo��)
	if (m_do_jump == true)
	{
		Jump();
	}

	//��ʒ[�Ƃ̓����蔻��
	if (m_pos.x <= -lrAdjustment)
	{
		m_pos.x += m_speed;
	}

	//�v���C���[����ʒ����Ɏ~�߂�̏���
	if (m_pos.x >= Centerofscreen)
	{
		m_pos.x -= m_speed;
	}

	//�v���C���[�ɏd�͂������鏈��
	if (m_pos.y <= P_posX)
	{
		m_pos.y += Gravity;
	}
}

void TrpPlayer::ReleaseNote()
{
	for (int i = 0; i < 3; i++)
	{
		notebox[i] = 0;
	}
	
	//�����̉��t(�X�g�b�N)�����ׂĔj������
	for (int i = 0; i < 6; i++)
	{
		m_play_note[i] = false;
	}
}

void TrpPlayer::InitAnimation()
{
		static float R_X=0, R_Y=0;
		//�z��ɉ摜��؂蔲���傫��������Ă���
		for (m_i = 0; m_i < MaxAnimationNum; m_i++)
		{
			
				Animation[m_i].m_RectX = R_X;
				Animation[m_i].m_RectY = R_Y;
				Animation[m_i].m_Rect_Height = Rect_Height;
				Animation[m_i].m_Rect_Width = Rect_Width;
				Animation[m_i].m_Display_Flame = Dispflame;

				R_X += RectX;

				if (R_X >= MaxRectX)
				{
					if (R_Y <= MaxRectY)
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

void TrpPlayer::GetMotion(int Llist_, int Rlist_)
{
	//�v���C���[���E�����Ȃ�E�����̉摜��ϐ��ɓ����
	if (m_direction == RIGHT)
	{
		m_List = Rlist_;
	}
	//�������Ȃ獶�����̉摜��ϐ��ɓ����
	if (m_direction == LEFT)
	{
		m_List = Llist_;
	}
}

void TrpPlayer::DrawAnimation()
{
	//�v���C���[�̌������E�����Ȃ�
	if (m_direction == RIGHT)
	{
		Animation[m_i].m_Display_Flame--;
		//DisplayFlame��0��菬������Εϐ��ɒ萔Dispflame������
		if (Animation[m_i].m_Display_Flame <= 0)
		{
			Animation[m_i].m_Display_Flame = Dispflame;
			m_i++;
			//�؂蔲�����摜���Ō�܂ŗ�����ŏ��ɖ߂�
			if (m_i >= MaxAnimationNum)
			{
				m_i = 0;
			}
		}
	}
	//�v���C���[���������Ȃ火����
	if (m_direction == LEFT)
	{
		
		Animation[m_i].m_Display_Flame--;
		if (Animation[m_i].m_Display_Flame <= 0)
		{
			Animation[m_i].m_Display_Flame = Dispflame;
			m_i++;
			if (m_i >= MaxAnimationNum)
			{
				m_i = 0;
			}
		}
	}
}


void TrpPlayer::Jump()
{
	static float jump_power = P_jump_power;

	//�v���C���[��Damage��ԁAAttack��ԂłȂ���΃W�����v��Ԃɂ���
	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump;
	}

	m_pos.y -= jump_power;
	jump_power -= Gravity;

	//�v���C���[���n��(�W�����v�J�n�O��Y���W)�ɂ�����W�����v��Ԃ���������
	if (m_pos.y >= P_posY)
	{
		jump_power = P_jump_power;	
		m_do_jump = false;
		m_is_active = false;
	}
}