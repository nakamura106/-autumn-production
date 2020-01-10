#include "ShitBullet.h"
#include"../Engine/FlameTimer.h"

ShitBullet::ShitBullet(
	float x_,
	float y_,
	float move_speed_,
	float acceleration_,
	Direction direction_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_	,
	int tex_split_h_	,
	int tex_split_all	
)
	:EnemyBullet(x_, y_, move_speed_, direction_, use_tex_, tex_split_w_, tex_split_h_, tex_split_all)
{

	m_is_dropdown		= false;
	m_savetime_delete	= 0;
	m_acceleration		= acceleration_;

}



void ShitBullet::MoveUpdate()
{

	if (m_pos.y + M_BULLET_SYZE >= G_GROUND_POS_Y) {

		if (m_is_dropdown != true) {
			//���݂̃t���[�����Z�b�g
			m_savetime_delete = FlameTimer::GetNowFlame();

			//�X�g�b�v
			m_pos.y = G_GROUND_POS_Y - M_BULLET_SYZE;

			m_is_dropdown = true;

		}

		if (FlameTimer::GetNowFlame(m_savetime_delete) >= M_DELETE_TIME) {

			//�I�u�W�F�N�g����
			m_is_delete = true;

		}


	}
	else {

		//�n�ʂɌ������ė����Ă���
		m_pos.y += m_speed;

		//����
		m_speed += m_acceleration;

	}

}