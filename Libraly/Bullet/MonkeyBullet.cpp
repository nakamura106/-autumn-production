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

	m_is_jump		= true;
	m_init_speed_y	= move_speed_y_;
	m_move_limit	= 4000.f;
	m_draw_param.tu = 3.f;

	//�摜���]
	if (m_direction == Direction::RIGHT) {
		m_is_turn = true;
	}

}

MonkeyBullet::~MonkeyBullet()
{
}

void MonkeyBullet::MoveUpdate()
{

	CalcTexAngle();

	if (m_is_jump != true) {
		//�W�����v�J�n
		m_is_jump = true;

		m_speed_y = m_init_speed_y;
	}
	
	//��{�ړ�����
	BulletBase::MoveUpdate();

	//�X�s�[�h�ύX
	m_speed_y += m_acceleration_y;

	//�n�ʂɒ����ƁA�W�����vOFF
	if (CheckLandGround()) {

		m_pos.y = G_GROUND_POS_Y - m_draw_param.tex_size_y;

		m_is_jump = false;

	}
}

void MonkeyBullet::CalcTexAngle()
{
	//�`��p�x����
	if (m_direction == Direction::LEFT) {
		if (m_speed_y > 0.f) {
			//��яオ��Ƃ�
			m_draw_angle = 30;
		}
		else {
			m_draw_angle = 330;
		}
	}
	else {
		if (m_speed_y > 0.f) {
			//��яオ��Ƃ�
			m_draw_angle = 330;
		}
		else {
			m_draw_angle = 30;
		}
	}

}
