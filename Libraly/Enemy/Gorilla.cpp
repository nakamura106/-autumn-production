#include "Gorilla.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla)
{
	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	//ゴリラだけ例外。眠り状態のみ異なる
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;
}

Gorilla::~Gorilla()
{
}

void Gorilla::Init()
{
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

}

EnemyAIType Gorilla::ChangeAIType()
{
	return EnemyAIType::AI1;
}

void Gorilla::EnemyAttack1()
{
	//ドラミング
}

void Gorilla::EnemyAttack2()
{
	//叩きつけ
}

void Gorilla::EnemyAttack3()
{
	//バナナ投げ
}

void Gorilla::EnemyFly()
{
	//ジャンプ
}
