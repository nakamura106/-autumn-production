#include "ShitBullet.h"
#include"../Engine/FlameTimer.h"
#include "../Collision/ShapeType/ShapeCircle.h"

ShitBullet::ShitBullet(
	float x_,
	float y_,
	float move_speed_,
	float move_speed_y_,
	float acceleration_,
	Direction direction_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all
)
	:EnemyBullet(x_, y_, move_speed_, direction_, 0, move_speed_y_, acceleration_, use_tex_, tex_split_w_, tex_split_h_, tex_split_all)
{

	m_is_dropdown = false;
	m_savetime_delete = 0;

	m_shape_list.push_back(new ShapeCircle(m_pos.x, 54.0f, m_pos.y, 83.0f, 26.0f, 128.0f));

}



void ShitBullet::MoveUpdate()
{

	if (m_pos.y + m_draw_param.tex_size_y*1.5f >= G_GROUND_POS_Y) {

		if (m_is_dropdown != true) {
			//現在のフレームをセット
			m_savetime_delete = FlameTimer::GetNowFlame();

			//ストップ
			m_pos.y = G_GROUND_POS_Y - m_draw_param.tex_size_y*1.5f;

			m_is_dropdown = true;

		}

		if (FlameTimer::GetNowFlame(m_savetime_delete) >= M_DELETE_TIME) {

			//オブジェクト消滅
			m_is_delete = true;

		}


	}
	else {

		//地面に向かって落ちていく
		m_pos.y += m_speed_y;

		if (m_direction == Direction::LEFT) {
			m_map_pos -= m_speed;
		}
		else {
			m_map_pos += m_speed;
		}

		//加速
		m_speed_y += m_acceleration_y;

	}

}
