#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(
	float x_,
	float y_,
	float move_speed_,
	Direction direction_,
	int draw_angle_,
	float move_speed_y_,
	float acceleration_y_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all,
	int tex_use_num_,
	float active_distance_
)
	:BulletBase(x_, y_, move_speed_, direction_, ObjectRavel::Ravel_EnemyBullet, move_speed_y_, draw_angle_)
{

	m_draw_param.texture_id = use_tex_;
	m_anim_param.split_all = tex_split_all;
	m_anim_param.split_width = tex_split_w_;
	m_anim_param.split_height = tex_split_h_;
	m_acceleration_y = acceleration_y_;
	m_tex_use_num = tex_use_num_;
	m_move_limit = active_distance_;

	CalcTexUseNum();

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{
	
}

void EnemyBullet::Update()
{
	BulletBase::Update();
}

void EnemyBullet::CalcTexUseNum()
{
	if (m_direction == Direction::RIGHT) {
		m_is_turn = true;
	}

	if (m_tex_use_num != 0) {

		int tmp = m_tex_use_num % m_anim_param.split_width;

		m_draw_param.tu = m_draw_param.tv = 0.f;

		if (tmp == 0) {
			m_draw_param.tu = m_anim_param.split_width;
			--m_draw_param.tv;
		}
		else {
			m_draw_param.tu = tmp;
		}

		m_draw_param.tv += static_cast<int>(m_tex_use_num / m_anim_param.split_width);

		if (GetAnimationTexNum() > m_anim_param.split_all) {

			m_draw_param.tv = 1.f;

			m_draw_param.tu = 1.f;

		}

	}
}
