#include "BulletBase.h"


BulletBase::BulletBase(
	float x_, 
	float y_, 
	float move_speed_, 
	Direction direction_,
	ObjectRavel obj_ravel_,
	float speed_y_,
	int draw_angle_,
	float tex_size
)
	:ObjectBase(obj_ravel_,direction_,move_speed_,draw_angle_)
{
	//�I�u�W�F�N�g����̏����i�[
	m_pos.x	= x_;
	m_map_pos = x_;
	m_pos.y = y_;

	//�g�p�摜�ݒ�
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_draw_param.tex_size_x = tex_size;
	m_draw_param.tex_size_y = tex_size;

	//�A�j���[�V�����p�������o������
	m_anim_param.split_all		= 16;
	m_anim_param.split_width	= 4;
	m_anim_param.split_height	= 4;
	m_anim_param.change_flame	= 10;

	//�����蔻��p
	m_rect_param.shift_x = tex_size / 2.f;
	m_rect_param.shift_y = tex_size / 2.f;
	m_rect_param.width = tex_size;
	m_rect_param.height = tex_size;

	//�ړ���������p
	m_move_count		= 0.f;
	m_move_limit		= M_MOVE_LIMIT_DEFAULT;
	m_speed_y			= speed_y_;

	CalcDrawPosition();

	if (m_anim_param.split_all >= 2) {

		if (m_direction == Direction::LEFT) {
			m_draw_param.tu = 1.f;
		}
		else {
			m_draw_param.tu = 2.f;
		}
	}
}

BulletBase::~BulletBase()
{

}

void BulletBase::Init()
{
	//�摜���ǂݍ���
	//Load();


}

void BulletBase::Update()
{
	ObjectBase::Update();

	MoveUpdate();

	CalcDrawPosition();
}

void BulletBase::Load()
{
}



void BulletBase::MoveUpdate()
{
	
	//�����ɂ���Ĕ�ԕ������ω�
	if (m_direction == Direction::RIGHT) {
		m_map_pos += m_speed;
	}
	else if(m_direction==Direction::LEFT){
		m_map_pos -= m_speed;
	}

	//y�������
	m_pos.y += m_speed_y;
	
	//�L���������J�E���g
	m_move_count += m_speed;

	if (m_move_count >= m_move_limit) {

		m_is_delete = true;

	}
	if (m_pos.y >= G_GROUND_POS_Y) {

		m_is_delete = true;

	}
	
}
