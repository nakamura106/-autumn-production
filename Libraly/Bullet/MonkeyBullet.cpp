#include"MonkeyBullet.h"

MonkeyBullet::MonkeyBullet(
	float x_,
	float y_,
	float move_speed_,
	Direction direction_,
	float move_speed_y_,
	float acceleration_y_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all
)
	:EnemyBullet(x_, y_, move_speed_, direction_, 0, move_speed_y_, acceleration_y_, use_tex_, tex_split_w_, tex_split_h_, tex_split_all)
{

	m_is_jump		= false;
	m_init_speed_y	= move_speed_y_;
	m_move_limit	= 2000.f;

}

MonkeyBullet::~MonkeyBullet()
{
}

void MonkeyBullet::MoveUpdate()
{
	
	if (m_is_jump == true) {
		//基本移動動作
		BulletBase::MoveUpdate();

		//スピード変更
		m_speed_y -= m_acceleration_y;

		//地面に着くと、ジャンプOFF
		if (CheckLandGround()) {

			m_pos.y = G_GROUND_POS_Y - m_draw_param.tex_size_y;

			m_is_jump;

		}
	}
	else {
		//ジャンプ開始
		m_is_jump = true;

		m_speed_y = m_init_speed_y;

	}
}
