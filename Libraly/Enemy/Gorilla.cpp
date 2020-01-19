#include "Gorilla.h"
#include"../Bullet/BananaBullet.h"
#include"../Bullet/MonkeyBullet.h"

Gorilla::Gorilla()
	:EnemyBase(0.f,EnemyID::Gorilla)
{
	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	//�S����������O�B�����Ԃ݈̂قȂ�
	m_anim_param.split_all = 16;
	m_anim_param.split_width = m_anim_param.split_height = 4;

	//��̈ʒu�ݒ�
	m_hand_pos.x = m_draw_param.tex_size_x / 2.f - 100.f;
	m_hand_pos.y = m_draw_param.tex_size_y / 2.f;

	m_jump_acceleration = M_JUMP_ACCELERATION_DEFAULT;
	m_do_doraming = false;
	m_jump_speed = 0.f;
	m_end_jump = false;

}

Gorilla::~Gorilla()
{
}

void Gorilla::Init()
{
	
}

EnemyAIType Gorilla::ChangeAIType()
{
	return EnemyAIType::AI1;
}

void Gorilla::EnemyAttack1()
{
	//�h���~���O
	//�h���~���O���̓v���C���[�e�𖳌���
	m_do_doraming = true;
}

void Gorilla::EnemyAttack2()
{
	//�@����
}

void Gorilla::EnemyAttack3()
{
	//�o�i�i����
	if (m_do_bullet != true) {
		CreateBanana();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyAttack4()
{
	//�T������
	if (m_do_bullet != true) {
		CreateMonkey();
		m_do_bullet = true;
	}
}

void Gorilla::EnemyFly()
{
	//�W�����v
	//���ɃW�����v���I����Ă���ꍇ�A���얳��

	if (m_end_jump == true) {
		if (m_is_animation_end == true) {
			ChangeState(EnemyStateType::Wait);
		}

		return;
	}

	if (m_is_flying == true) {
		//�W�����v��
		EnemyBase::EnemyMove();

		m_pos.y -= m_jump_speed;

		m_jump_speed -= m_jump_acceleration;

		if (m_pos.y >= M_INIT_POS_Y) {

			m_pos.y = M_INIT_POS_Y;

			m_animation_stop = false;

			m_is_flying = false;

			m_end_jump = true;

		}

	}
	else {
		if (GetAnimationTexNum() >= M_JUMP_STOP_ANIM_FLAME) {

			m_is_flying = true;

			m_animation_stop = true;
		}
	}

}

void Gorilla::InitAllState()
{
	EnemyBase::InitAllState();

	m_do_doraming = false;
}

void Gorilla::InitSleepState()
{
	//���胂�[�V�����͉摜�g�p�������قȂ�
	m_anim_param.split_all = 8;
}

void Gorilla::InitFlyState()
{

	EnemyBase::InitFlyState();

	m_jump_speed = M_JUMP_SPEED_DEFAULT;
	m_end_jump = false;
}

void Gorilla::CreateBanana()
{
	Position b_pos = GetShotPos();

	bullet_list.push_back(
		new BananaBullet(
			b_pos.x,
			b_pos.y,
			m_speed,//x���x
			-m_speed,//y���x
			0.25f,//�����x
			(Direction)m_direction,
			this,
			12//�����n�߂�A�j���[�V�����ԍ�
		)
	);
}

void Gorilla::CreateMonkey()
{
	float pos_x = 0.f;

	Direction move_direction = Direction::LEFT;

	if (m_direction == Direction::LEFT) {
		pos_x = -300.f;
		move_direction = Direction::RIGHT;
	}
	else {
		pos_x = 3600.f;//�}�b�v�E�[
		move_direction = Direction::LEFT;
	}

	bullet_list.push_back(
		new MonkeyBullet(
			pos_x,
			m_pos.y + m_draw_param.tex_size_y / 2.f,
			m_speed/2.f,//x���x
			move_direction,
			-m_speed,//y���x
			0.15f//�����x
		)
	);
}
