#include "BananaBullet.h"

BananaBullet::BananaBullet(
	float x_, 
	float y_, 
	float move_speed_, 
	float move_speed_y_, 
	float acceleration_, 
	Direction direction_, 
	EnemyBase* parent_,
	int move_start_anim_num_
):ShitBullet(x_,y_,move_speed_,move_speed_y_,acceleration_,direction_,GameCategoryTextureList::GameEnemy_Bullet_Shit,4,2,1)
{
	m_parent = parent_;
	m_move_start_anim_num = move_start_anim_num_;
	m_is_move = false;
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

	}
	else {
		//�e�ł���I�u�W�F�N�g�̎�̈ʒu��
		//�����̍��W�����킹��
		Position hand_pos = m_parent->GetHandPos();

		m_map_pos = hand_pos.x;
		m_pos.y = hand_pos.y;
	}
}
