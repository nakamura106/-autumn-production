#include"TrpPlayer.h"
#include"../Engine/Graphics.h"
//#include"../Texture/Texture.h"
#include"../Object/Definition.h"
#include"../Engine/Vec.h"
#include"../Engine/Input.h"
#include"../Map/Map.h"





TrpPlayer::TrpPlayer()
{
	
}

TrpPlayer::~TrpPlayer()
{

}

void TrpPlayer::Init()
{
	player.m_is_delete = false;
	player.m_is_invincible = false;
	player.m_do_jump = false;
	player.m_is_active = false;
	player.m_hp = P_MaxHP;
	player.m_direction = RIGHT;
	player.m_speed = P_speed;
	player.m_state = (int)P_State::Wait;
	player.m_Key = (int)Key::Major;
	player.m_i = 0;
	player.m_map_pos = P_posX;
	player.m_pos.x = P_posX;
	player.m_pos.y = P_posY;
	player.m_List = GamePlayer_Taiki_Tp_RightTex;
	for (int i = 0; i < 6; i++)
	{
		player.m_play_note[i] = false;
	}
	player.Load();
	player.InitAnimation();
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
	player.P_Controll();
	player.UpdateAnimation();
	player.DrawAnimation();
	/*if (バレットのXがplayerのrange超えたら処理を行う)
	{
		ReleaseNote();
	}*/
}

void TrpPlayer::UpdateAnimation()
{
	//削除判定がfalse(削除処理が実行されない)ならモーションごとにTextureidを送る
	if (player.m_is_delete == false)
	{
		switch (m_state)
		{
		case (int)P_State::Wait:
			player.GetMotion(GamePlayer_Taiki_Tp_LeftTex, GamePlayer_Taiki_Tp_RightTex);
			break;
		
		case(int)P_State::Move:
			player.GetMotion(GamePlayer_Walk_Tp_LeftTex, GamePlayer_Walk_Tp_RightTex);
			break;
		
		case(int)P_State::Jump:
			player.GetMotion(GamePlayer_Jump_Tp_LeftTex, GamePlayer_Jump_Tp_RightTex);
			break;
		
		case(int)P_State::Jump_Attack:
			player.GetMotion(GamePlayer_JumpAttack_Tp_LeftTex, GamePlayer_JumpAttack_Tp_RightTex);
			break;
		
		case(int)P_State::Jump_Damage:
			player.GetMotion(GamePlayer_JumpDamage_Tp_LeftTex, GamePlayer_JumpDamage_Tp_RightTex);
			break;
		
		case(int)P_State::Damage:
			player.GetMotion(GamePlayer_Damage_Tp_LeftTex, GamePlayer_Damage_Tp_RightTex);
			break;
		
		case(int)P_State::Attack:
			player.GetMotion(GamePlayer_Attack_Tp_LeftTex, GamePlayer_Attack_Tp_RightTex);
			break;
		
		default:
			break;
		}
	}
}

void TrpPlayer::Draw()
{
	DrawUVTexture(m_pos.x, m_pos.y, Animation[m_i].m_Rect_Width, Animation[m_i].m_Rect_Height, GetTexture(TEXTURE_CATEGORY_GAME, m_List), Animation[m_i].m_RectX, Animation[m_i].m_RectY);
}

Position TrpPlayer::GetPos(int select)
{

	return player.m_pos.y;
}

void TrpPlayer::P_Controll()
{
	/*ボタンを離した後にモーションが
	継続してしまわないようにする処理*/
	if (player.m_is_active == true)
	{
		player.m_is_active = false;
	}
	
	// ※までボタン処理

	//右移動
	if (GetKey(RIGHT_KEY) == true)
	{
		player.m_state = (int)P_State::Move;
		if (player.m_direction == LEFT) {
			player.m_pos.x += lrAdjustment;
		}
		if (player.m_map_pos <= 3800)
		{
			player.m_map_pos += m_speed;
		}
		player.m_direction = RIGHT;
		player.m_pos.x += m_speed;
		player.m_is_active = true;
	}

	//左移動
	if (GetKey(LEFT_KEY) == true)
	{
		player.m_state = (int)P_State::Move;
		if (player.m_direction == RIGHT) {
			player.m_pos.x -= lrAdjustment;
		}
		if (player.m_map_pos >= 0)
		{
			player.m_map_pos -= player.m_speed;
		}
		if (player.m_map_pos <= player.m_pos.x)
		{
			player.m_pos.x -= player.m_speed;
		}
		player.m_direction = LEFT;
		player.m_is_active = true;
	}

	//ジャンプ処理
	if (GetKey(SPACE_KEY) == true)
	{
		player.m_do_jump = true;
		player.m_is_active = true;
	}

	//長調短調切り替え処理(押している間のみ)
	if (GetKey(SHIFT_KEY) == true)
	{
		player.m_Key = (int)Key::Minor;
	}
	else
	{
		player.m_Key = (int)Key::Major;
	}

	//音符生成
	if (GetKey(ONE_KEY) == true)
	{
		if (player.m_play_note[3] != true && player.m_Key == (int)Key::Major)
		{
			player.m_play_note[0] = true;
		}
		if (player.m_play_note[0]!=true&& player.m_Key == (int)Key::Minor)
		{
			player.m_play_note[3] = true;
		}
	}

	//音符生成
	if (GetKey(TWO_KEY) == true)
	{
		if (player.m_play_note[4] != true && player.m_Key == (int)Key::Major)
		{
			player.m_play_note[1] = true;
		}
		if (player.m_play_note[1] != true && player.m_Key == (int)Key::Minor)
		{
			player.m_play_note[4] = true;
		}
	}

	//音符生成
	if (GetKey(THREE_KEY) == true)
	{
		if (player.m_play_note[5] != true && player.m_Key == (int)Key::Major)
		{
			player.m_play_note[2] = true;
		}
		if (player.m_play_note[2] != true && player.m_Key == (int)Key::Minor)
		{
			player.m_play_note[5] = true;
		}
	}
	// ※

	//activeがfalseなら待機状態にする処理
	if (player.m_is_active == false)
	{
		player.m_state = (int)P_State::Wait;
	}

	//プレイヤーがジャンプしているか判定する(しているならジャンプ関数を呼び出す)
	if (player.m_do_jump == true)
	{
		Jump();
	}

	//画面端との当たり判定
	if (player.m_pos.x <= -lrAdjustment)
	{
		player.m_pos.x += player.m_speed;
	}

	//プレイヤーを画面中央に止めるの処理
	if (player.m_pos.x >= Centerofscreen)
	{
		player.m_pos.x -= player.m_speed;
	}

	//プレイヤーに重力をかける処理
	if (player.m_pos.y <= P_posX)
	{
		player.m_pos.y += Gravity;
	}
}

void TrpPlayer::ReleaseNote()
{
	//音符の演奏(ストック)をすべて破棄する
	for (int i = 0; i < 6; i++)
	{
		player.m_play_note[i] = false;
	}
}

void TrpPlayer::InitAnimation()
{
		static float R_X=0, R_Y=0;
		//配列に画像を切り抜く大きさをいれていく
		for (player.m_i = 0; player.m_i < MaxAnimationNum; player.m_i++)
		{
			
				player.Animation[m_i].m_RectX = R_X;
				player.Animation[m_i].m_RectY = R_Y;
				player.Animation[m_i].m_Rect_Height = Rect_Height;
				player.Animation[m_i].m_Rect_Width = Rect_Width;
				player.Animation[m_i].m_Display_Flame = Dispflame;

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
	if (player.m_direction == RIGHT)
	{
		player.m_List = Rlist_;
	}
	//左向きなら左向きの画像を変数に入れる
	if (player.m_direction == LEFT)
	{
		player.m_List = Llist_;
	}
}

void TrpPlayer::DrawAnimation()
{
	//プレイヤーの向きが右向きなら
	if (player.m_direction == RIGHT)
	{
		player.Animation[m_i].m_Display_Flame--;
		//DisplayFlameが0より小さければ変数に定数Dispflameを入れる
		if (player.Animation[m_i].m_Display_Flame <= 0)
		{
			player.Animation[m_i].m_Display_Flame = Dispflame;
			player.m_i++;
			//切り抜いた画像が最後まで来たら最初に戻す
			if (player.m_i >= MaxAnimationNum)
			{
				player.m_i = 0;
			}
		}
	}
	//プレイヤーが左向きなら↓同文
	if (player.m_direction == LEFT)
	{
		
		player.Animation[m_i].m_Display_Flame--;
		if (player.Animation[m_i].m_Display_Flame <= 0)
		{
			player.Animation[m_i].m_Display_Flame = Dispflame;
			player.m_i++;
			if (player.m_i >= MaxAnimationNum)
			{
				player.m_i = 0;
			}
		}
	}
}


void TrpPlayer::Jump()
{
	static float jump_power = P_jump_power;

	//プレイヤーがDamage状態、Attack状態でなければジャンプ状態にする
	if (player.m_state != (int)P_State::Damage && player.m_state != (int)P_State::Attack)
	{
		player.m_state = (int)P_State::Jump;
	}

	player.m_pos.y -= jump_power;
	jump_power -= Gravity;

	//プレイヤーが地面(ジャンプ開始前のY座標)についたらジャンプ状態を解除する
	if (player.m_pos.y >= P_posY)
	{
		jump_power = P_jump_power;	
		player.m_do_jump = false;
		player.m_is_active = false;
	}
}