#include "Gorilla.h"
#include"../Bullet/BananaBullet.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla)
{
	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	//�S����������O�B�����Ԃ݈̂قȂ�
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;

	//��̈ʒu�ݒ�
	m_hand_pos.x = m_draw_param.tex_size_x / 2.f - 100.f;
	m_hand_pos.y = m_draw_param.tex_size_y / 2.f;
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

	//�e
	LoadTexture("Res/Tex/Enemy/Gorilla/Boss3_Bullet.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Shit);

}

EnemyAIType Gorilla::ChangeAIType()
{
	return EnemyAIType::AI1;
}

void Gorilla::EnemyAttack1()
{
	//�h���~���O
}

void Gorilla::EnemyAttack2()
{
	//�@����
}

void Gorilla::EnemyAttack3()
{
	//�o�i�i����
	if (m_do_bullet != true) {
		CreateBanana();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyFly()
{
	//�W�����v
}

void Gorilla::CreateBanana()
{
	Position b_pos = GetShotPos();

	bullet_list.push_back(
		new BananaBullet(
			b_pos.x,
			b_pos.y,
			m_speed,//x���x
			-m_speed,//y���x
			0.25f,//�����x
			(Direction)m_direction,
			this,
			12//�����n�߂�A�j���[�V�����ԍ�
		)
	);
}
