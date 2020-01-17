#include"GameSceneLoad.h"
#include"../../Texture/Texture.h"
#include"../../DataBank/DataBank.h"
#include"../../Object/Definition.h"



void GameSceneLoad()
{


	switch (DataBank::Instance()->GetMapType())
	{
	case (int)MapType::CityMap:
		//!<街マップの画像読込
		LoadTexture("Res/Tex/Map/街/Town2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
		LoadTexture("Res/Tex/Map/街/Town3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
		LoadTexture("Res/Tex/Map/街/Town4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);
		LoadTexture("Res/Tex/Map/街/Town1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
		//!<街マップの画像読込ここまで


		//!<ゴリラの画像読込
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Jump_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SkyWaitLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Jump_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SkyWaitRight);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Walk_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Walk_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);

		//LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_DramingAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Left);
		//LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_DramingAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Right);
		//LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_TatakitukeAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Left);
		//LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_TatakitukeAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Right);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_NageBananaAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Left);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_NageBananaAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Right);

		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitRight);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);

		//弾
		LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Bullet.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Shit);
		//!<ゴリラの画像読込ここまで
		break;
	case (int)MapType::SeaMap:
		//!<海マップの画像読込
		LoadTexture("Res/Tex/Map/海/Sea2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
		LoadTexture("Res/Tex/Map/海/Sea3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
		LoadTexture("Res/Tex/Map/海/Sea4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);
		LoadTexture("Res/Tex/Map/海/Sea1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
		//!<海マップの画像読込ここまで


			//!< 鳥の画像読込
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Habataki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FlappingLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Habataki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FlappingRight);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_HaneAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Left);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_HaneAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Right);

		//注！この画像に限り、分割数が横4*縦4(使用枚数12)→8*4(24)に変更
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_DashAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Left);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_DashAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Right);

		//注！鳥は待機に二種類ある！
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SkyWaitLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SkyWaitRight);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_TaikiGround_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_TaikiGround_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitRight);

		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);

		//3つ目の攻撃フン落下で使用するモーションはただの羽ばたき
		//LoadTexture("Res/Tex/Enemy/Bird/Boss2_HeadAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Left);
		//LoadTexture("Res/Tex/Enemy/Bird/Boss2_HeadAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Right);

		//弾画像
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_Hun.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Shit);
		LoadTexture("Res/Tex/Enemy/Bird/Boss2_HaneGreen.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Normal);
		//!<鳥の画像読込ここまで
		break;
	case (int)MapType::WoodsMap:
		//!<森マップの画像読込
		LoadTexture("Res/Tex/Map/森/Woods2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
		LoadTexture("Res/Tex/Map/森/Woods3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
		LoadTexture("Res/Tex/Map/森/Woods4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);
		LoadTexture("Res/Tex/Map/森/Woods1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
		//!<森マップの画像読込ここまで


		//!<マップオブジェクトの画像読込
		LoadTexture("Res/Tex/Map/森/Grass Small.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject);
		LoadTexture("Res/Tex/Map/森/Grass Medium.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject2);
		LoadTexture("Res/Tex/Map/森/Grass Large.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject3);
		//!<マップオブジェクトの画像読込ここまで

		//!<ネズミ画像読込
		/*11/26 注!!仮実装のコード*/
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Walk_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Walk_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitLeft);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WaitRight);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_DashAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Left);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_DashAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack1Right);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_TogeAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Left);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_TogeAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack2Right);
		LoadTexture("Res/Tex/Enemy/Mouse/Boss1_FlyNeedle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Normal);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_HeadAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Left);
		LoadTexture("Res/Tex/Enemy/Mouse_Half/Boss1_HeadAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Attack3Right);
		//!<ネズミ画像読込ここまで
		break;
	default:
		break;
	}
	

	switch (DataBank::Instance()->GetPlayerType())
	{
	case (int)Player::PlayerTypeTrumpet:
		//!<トランペットプレイヤーの画像読込
		LoadTexture("Res/Tex/TrpPlayer/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Taiki_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Attack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Attack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Damage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Damage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Jump_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Jump_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_JumpAttack_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_JumpAttack_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_JumpDamage_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_JumpDamage_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_RightTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Walk_Tp_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_LeftTex);
		LoadTexture("Res/Tex/TrpPlayer/Player_Walk_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_RightTex);
		//!<トランペットプレーヤーここまで
		break;
	case (int)Player::PlayerTypeFlute:
		
		break;
	case (int)Player::PlayerTypeTuba:
		//!<チューバプレイヤー画像読込
		LoadTexture("Res/Tex/TubaPlayer/Player_Taiki_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Taiki_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Attack_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Attack_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Attack_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Damage_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Damage_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Damage_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Jump_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Jump_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Jump_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_JumpAttack_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_JumpAttack_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpAttack_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_JumpDamage_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_JumpDamage_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_JumpDamage_RightTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Walk_Tb_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_LeftTex);
		LoadTexture("Res/Tex/TubaPlayer/Player_Walk_Tb_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Walk_RightTex);
		//!<チューバプレイヤー画像読込ここまで
		break;
	default:
		break;
	}









	//!<プレイヤー弾読込
	LoadTexture("Res/Tex/Effect/tyotyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
	LoadTexture("Res/Tex/Effect/tyotyo02_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_2Tex);
	LoadTexture("Res/Tex/Effect/tantyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_3Tex);
	LoadTexture("Res/Tex/Effect/tantyo02_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_4Tex);
	//!<プレイヤー弾読込ここまで


	


	


	//!<UI画像読込
	LoadTexture("Res/Tex/EnemyUi/FatigueGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyFatigueGauge);
	LoadTexture("Res/Tex/EnemyUi/FatigueCircle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyFatigueCircle);
	LoadTexture("Res/Tex/EnemyUi/AutoHealGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyAutoHealGauge);

	LoadTexture("Res/Tex/Chabon Melody/Blue_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueCenter);
	LoadTexture("Res/Tex/Chabon Melody/Blue_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueLeft);
	LoadTexture("Res/Tex/Chabon Melody/Blue_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueRight);
	LoadTexture("Res/Tex/Chabon Melody/Green_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_GreenCenter);
	LoadTexture("Res/Tex/Chabon Melody/Pink_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_PinkCenter);
	LoadTexture("Res/Tex/Chabon Melody/Purple_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_PurpleRight);
	LoadTexture("Res/Tex/Chabon Melody/Red_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedCenter);
	LoadTexture("Res/Tex/Chabon Melody/Red_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedLeft);
	LoadTexture("Res/Tex/Chabon Melody/Red_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedRight);
	LoadTexture("Res/Tex/Chabon Melody/Yellow_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_YellowRight);

	LoadTexture("Res/Tex/Life/HP0.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_1Tex);
	LoadTexture("Res/Tex/Life/HP1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_2Tex);
	LoadTexture("Res/Tex/Life/HP2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_3Tex);
	LoadTexture("Res/Tex/Life/HP3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_4Tex);

	LoadTexture("Res/Tex/EnemyUi/SleepGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemySleepGauge);
	LoadTexture("Res/Tex/EnemyUi/SleepCircle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemySleepCircle);

	LoadTexture("Res/Tex/EnemyUi/EnemyAchieve.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyAchieveUi);

	LoadTexture("Res/Tex/EnemyUi/LifeBaseBar.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyUi);

	LoadTexture("Res/Tex/Performance Symbol.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerUi);
	//!<UI画像読込ここまで


	//!<エフェクト画像読込
	LoadTexture("Res/Tex/Effect/debuff_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameDebuffEffect);
	LoadTexture("Res/Tex/Effect/die_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameDieEffect);
	LoadTexture("Res/Tex/Effect/failure_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFailureEffect);
	LoadTexture("Res/Tex/Effect/hit_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameHitEffect);
	LoadTexture("Res/Tex/Effect/Landing_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameLandingEffect);
	LoadTexture("Res/Tex/Effect/shot_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameShotEffect);
	LoadTexture("Res/Tex/Effect/sleep_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameSleepEffect);
	LoadTexture("Res/Tex/Effect/sweat_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameSweatEffect);
	//!<エフェクト画像読込ここまで




}