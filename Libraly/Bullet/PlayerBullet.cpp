#include "PlayerBullet.h"
#include "../DataBank/DataBank.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Manager/CollisionManager.h"

PlayerBullet::PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_)
	:BulletBase(x_, y_, move_speed_, direction_,ObjectRavel::Ravel_PlayerBullet)
{
	m_draw_param.texture_id		= GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_anim_param.split_all		= M_PBULLET_ANIM_SPLIT_ALL;
	m_anim_param.split_width	= M_PBULLET_ANIM_SPLIT_W;
	m_anim_param.split_height	= M_PBULLET_ANIM_SPLIT_H;
	player_bullet_type			= p_bullet_type_;

	//�v���C���[�̒e�̏����i�[
	SetPlayerBulletInfo();

	m_shape_list.push_back(new ShapeCircle(this->GetPos().x, this->GetPos().y, 50.0f));
}

PlayerBullet::~PlayerBullet()
{
	for (const auto& i : m_shape_list)
	{
		delete i;
	}
}

void PlayerBullet::Load()
{
	//LoadTexture("Res/Tex/Effect/tyotyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void PlayerBullet::SetPlayerBulletInfo()
{
	switch (player_bullet_type)
	{
	case PlayerBulletType::Chocho_1:
		//�g�p����e�N�X�`����ݒ�
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;

		//�I�u�W�F�N�g�̎��(���x��)�ݒ�
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet;

		// UI�pBulletType�n���֐�
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_1);

		//���̒e���������蔻�莞�̏���ݒ�
		m_hit_use_atk = M_CHOCHO_1_NUM;

		break;

	case PlayerBulletType::Chocho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_2Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet2;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_2);
		m_hit_use_atk = M_CHOCHO_2_NUM;
		break;

	case PlayerBulletType::Tancho_1:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_3Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet3;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_1);
		m_hit_use_atk = M_TANCHO_1_NUM;
		break;

	case PlayerBulletType::Tancho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_4Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet4;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_2);
		m_hit_use_atk = M_TANCHO_2_NUM;
		break;

	default:
		break;
	}
}

void PlayerBullet::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{
	if (ravel_ == ObjectRavel::Ravel_Boss) {
		m_is_delete = true;
	}
}

void PlayerBullet::Draw()
{
	DrawInversion(
		m_pos.x,					//x���W
		m_pos.y,					//y���W
		m_draw_param.tex_size_x,	//�e�N�X�`���̉��T�C�Y
		m_draw_param.tex_size_y,	//�e�N�X�`���̏c�T�C�Y		
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
		(m_draw_param.tu - 1) / m_anim_param.split_width,
		(m_draw_param.tv - 1) / m_anim_param.split_height,
	m_direction);
}

void PlayerBullet::Update()
{
	BulletBase::Update();

	AnimationUpdate();

	CollisionParamUpdate();
}

void PlayerBullet::CollisionParamUpdate()
{
	for (const auto& i : m_shape_list)
	{
		i->Update(this->GetPos().x, this->GetPos().y);
	}
	CollisionManager::GetInstance().AddPBulletColObject(this);
}
