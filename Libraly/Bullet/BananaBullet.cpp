#include "BananaBullet.h"
#include "../Collision/ShapeType/ShapeCircle.h"

BananaBullet::BananaBullet(
	float x_,
	float y_,
	float move_speed_,
	float move_speed_y_,
	float acceleration_,
	Direction direction_,
	EnemyBase* parent_,
	int move_start_anim_num_
) :ShitBullet(x_, y_, move_speed_, move_speed_y_, acceleration_, direction_, GameCategoryTextureList::GameEnemy_Bullet_Shit, 4, 1, 1)
{
	m_parent = parent_;
	m_move_start_anim_num = move_start_anim_num_;
	m_is_move = false;
	m_draw_param.tu = 1;

	m_shape_list.push_back(new ShapeCircle(m_pos.x, 58.0f, m_pos.y, 83.0f, 34.0f, 128.0f));
}

void BananaBullet::MoveUpdate()
{
	//�ŏ��͐e�ł���I�u�W�F�N�g�ɏ]���ē���
	if (m_parent->GetAnimationTexNum() >= m_move_start_anim_num) {
		m_is_move = true;
	}

	if(m_is_move==true){

		ShitBullet::MoveUpdate();

		if (m_is_dropdown != true) {

			//�o�i�i����]
			++m_draw_angle;
		}
		else {
			//�o�i�i�̗��������
			m_draw_angle = 0;
			m_draw_param.tu = 2;

			//�o�i�i�o���b�g�ɕύX
			m_obj_ravel = ObjectRavel::Ravel_BananaBullet;
		}

	}
	else {
		//�e�ł���I�u�W�F�N�g�̎�̈ʒu��
		//�����̍��W�����킹��
		Position hand_pos = m_parent->GetHandPos();

		m_map_pos = hand_pos.x - m_draw_param.tex_size_x / 2.f;
		m_pos.y = hand_pos.y - m_draw_param.tex_size_y / 2.f;
	}
}


