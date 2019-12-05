#include "BulletBase.h"

BulletBase::BulletBase(float x_, float y_, float move_speed_, Direction direction_)
{
	//�I�u�W�F�N�g����̏����i�[
	m_pos.x = x_;
	m_pos.y = y_;
	m_speed = move_speed_;
	m_direction = direction_;

	//�g�p�摜�ݒ�
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_draw_param.tex_size_x = M_BULLET_SYZE;
	m_draw_param.tex_size_y = M_BULLET_SYZE;

	//�A�j���[�V�����p�������o������
	m_anim_param.split_all		= 16;
	m_anim_param.split_width	= 4;
	m_anim_param.split_height	= 4;
	m_anim_param.change_flame	= 10;

	//�ړ���������p
	m_move_count		= 0.f;
	m_move_limit		= M_MOVE_LIMIT_DEFAULT;
}

BulletBase::~BulletBase()
{

}

void BulletBase::Init()
{
	//�摜���ǂݍ���
	Load();
}

void BulletBase::Update()
{
	MoveUpdate();

	AnimationUpdate();
}

void BulletBase::Load()
{
	LoadTexture("Res/Tex/Effect/attack1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void BulletBase::MoveUpdate()
{
	//�����ɂ���Ĕ�ԕ������ω�
	if (m_direction == Direction::RIGHT) {
		m_pos.x += m_speed;
	}
	else if(m_direction==Direction::LEFT){
		m_pos.x -= m_speed;
	}
	
	//�L���������J�E���g
	m_move_count += m_speed;

	if (m_move_count >= m_move_limit) {

		m_is_delete = true;

	}
	
}
