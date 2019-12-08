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
	/*if (バレットのXがplayerのrange超えたら処理を行う)
	{
		ReleaseNote();
	}*/
}

void TrpPlayer::UpdateAnimation()
{
	//削除判定がfalse(削除処理が実行されない)ならモーションごとにTextureidを送る
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
	if (m_play_note[0] == true)
	{
		DrawFont(40, 200, "1", Regular,Red);
	}
	if (m_play_note[1] == true)
	{
		DrawFont(60, 200, "2", Regular, Red);
	}
	if (m_play_note[2] == true)
	{
		DrawFont(80, 200, "3", Regular, Red);
	}
	if (m_play_note[3] == true)
	{
		DrawFont(100, 200, "4", Regular, Red);
	}
	if (m_play_note[4] == true)
	{
		DrawFont(120, 200, "5", Regular, Red);
	}
	if (m_play_note[5] == true)
	{
		DrawFont(140, 200, "6", Regular, Red);
	}
	
}


void TrpPlayer::P_Controll()
{

	static int atkcount = 0;
	static int count = 0;

	/*ボタンを離した後にモーションが
	継続してしまわないようにする処理*/
	if (m_is_active == true)
	{
		m_is_active = false;
	}
	
	// ※までボタン処理
	
	if (GetKey(A_KEY) == true)
	{
		ReleaseNote();
		
		//PlayerBullet(m_pos.x, m_pos.y, 10.0f, m_direction);
	}
	count++;
	//右移動
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

	//左移動
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

	//ジャンプ処理
	if (GetKey(SPACE_KEY) == true)
	{
		m_do_jump = true;
		m_is_active = true;
	}

	//長調短調切り替え処理(押している間のみ)
	if (GetKey(SHIFT_KEY) == true)
	{
		m_Key = (int)Key::Minor;
	}
	else
	{
		m_Key = (int)Key::Major;
	}


	//音符生成
	if (GetKey(ONE_KEY) == true)
	{
		if (m_play_note[3] != true && m_Key == (int)Key::Major)
		{
			m_play_note[0] = true;
			atkcount++;
		}
		if (m_play_note[0]!=true&& m_Key == (int)Key::Minor)
		{
			m_play_note[3] = true;
			atkcount++;
		}
	}

	//音符生成
	if (GetKey(TWO_KEY) == true)
	{
		if (m_play_note[4] != true && m_Key == (int)Key::Major)
		{
			m_play_note[1] = true;
			atkcount++;
		}
		if (m_play_note[1] != true && m_Key == (int)Key::Minor)
		{
			m_play_note[4] = true;
			atkcount++;
		}
	}

	//音符生成
	if (GetKey(THREE_KEY) == true)
	{
		if (m_play_note[5] != true && m_Key == (int)Key::Major)
		{
			m_play_note[2] = true;
			atkcount++;
		}
		if (m_play_note[2] != true && m_Key == (int)Key::Minor)
		{
			m_play_note[5] = true;
			atkcount++;
		}
	}
	// ※

	//activeがfalseなら待機状態にする処理
	if (m_is_active == false)
	{
		m_state = (int)P_State::Wait;
	}

	//プレイヤーがジャンプしているか判定する(しているならジャンプ関数を呼び出す)
	if (m_do_jump == true)
	{
		Jump();
	}

	//画面端との当たり判定
	if (m_pos.x <= -lrAdjustment)
	{
		m_pos.x += m_speed;
	}

	//プレイヤーを画面中央に止めるの処理
	if (m_pos.x >= Centerofscreen)
	{
		m_pos.x -= m_speed;
	}

	//プレイヤーに重力をかける処理
	if (m_pos.y <= P_posX)
	{
		m_pos.y += Gravity;
	}
}

void TrpPlayer::ReleaseNote()
{
	//音符の演奏(ストック)をすべて破棄する
	for (int i = 0; i < 6; i++)
	{
		m_play_note[i] = false;
	}
}

void TrpPlayer::InitAnimation()
{
		static float R_X=0, R_Y=0;
		//配列に画像を切り抜く大きさをいれていく
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
	//プレイヤーが右向きなら右向きの画像を変数に入れる
	if (m_direction == RIGHT)
	{
		m_List = Rlist_;
	}
	//左向きなら左向きの画像を変数に入れる
	if (m_direction == LEFT)
	{
		m_List = Llist_;
	}
}

void TrpPlayer::DrawAnimation()
{
	//プレイヤーの向きが右向きなら
	if (m_direction == RIGHT)
	{
		Animation[m_i].m_Display_Flame--;
		//DisplayFlameが0より小さければ変数に定数Dispflameを入れる
		if (Animation[m_i].m_Display_Flame <= 0)
		{
			Animation[m_i].m_Display_Flame = Dispflame;
			m_i++;
			//切り抜いた画像が最後まで来たら最初に戻す
			if (m_i >= MaxAnimationNum)
			{
				m_i = 0;
			}
		}
	}
	//プレイヤーが左向きなら↓同文
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

	//プレイヤーがDamage状態、Attack状態でなければジャンプ状態にする
	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump;
	}

	m_pos.y -= jump_power;
	jump_power -= Gravity;

	//プレイヤーが地面(ジャンプ開始前のY座標)についたらジャンプ状態を解除する
	if (m_pos.y >= P_posY)
	{
		jump_power = P_jump_power;	
		m_do_jump = false;
		m_is_active = false;
	}
}