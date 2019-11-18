#include"EnemyBase.h"

#define Num_of_TakeaBreak  100

EnemyBase::EnemyBase()
{
	m_Enemy_Id = Enemy::BossTypeMax;
	m_State = EnemyStateType::EnemyStateTypeMax;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{

}

void EnemyBase::Create()
{

}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{

}

int EnemyBase::GetEnemyPosX()		//�G�l�~�[��x���W���擾
{
	return m_pos.x;
}

int EnemyBase::GetEnemyPosY()		//�G�l�~�[��y���W���擾
{
	return m_pos.y;
}

void EnemyBase::UpdateState()		//�G�l�~�[�̏�Ԃ̍X�V
{
	switch (m_State)
	{
	case EnemyStateType::Idle:

		EnemyIdle();

		break;

	case EnemyStateType::Break:

		EnemyBreak();

		break;

	case EnemyStateType::Warn:

		EnemyMove();

		break;

	case EnemyStateType::Attack:

		EnemyAttack();

		break;

	case EnemyStateType::Refuge:

		EnemyRefuge();

		break;

	default:
		/*
			!!
		*/
		break;
	}
}

void EnemyBase::ChangeState()		//�G�l�~�[���s���������
{
	/*
		�G�l�~�[�̏�Ԃ̕ύX
	*/
}

void EnemyBase::EnemyMove()			//�G�l�~�[�ړ�
{
	/*
		�ʏ��Ԃ̃G�l�~�[�ړ�
	*/
}

void EnemyBase::EnemyRefuge()		//��J��Ԃ̓���
{
	/*
		�s���`��Ԃ̃G�l�~�[����
	*/
}

void EnemyBase::EnemyAttack()		//�G�l�~�[�U��
{
	/*
		�v���C���[�̏�Ԃɉ����čU�����ύX
	*/
}

void EnemyBase::EnemyIdle()			//�G�l�~�[�ҋ@
{
	/*
		�G�l�~�[�̑ҋ@�i���̏�őҋ@�A�j���[�V�����j
	*/
}

void EnemyBase::EnemyBreak()		//�G�l�~�[�x�e
{
	/*
		�G�l�~�[�̔�J�ҋ@�i���̏�Ŕ�J�ҋ@�A�j���[�V�����j
	*/
}


