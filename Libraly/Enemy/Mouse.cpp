#include "Mouse.h"

//#include "HedgeHog.h"
//#include "Player/TrpPlayer.h"
//
////�萔�l�͉�����
//
//#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
//#define Limit_of_BreakTime 100		//MAX�̋x�e����
//#define Cure_of_SleepinessPoint 1	//���ԉ񕜂��閰�C�̒l
//#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
//#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���
//#define Gauge_Variable 100			//�Q�[�W���ߗp
//#define Attack_Interval	100			//�U���Ԋu
//
//Hedgehog::Hedgehog()
//{
//	m_Enemy_Id = Enemy::Hedgehog;
//	m_State = EnemyStateType::Warn;
//	m_attack_repertory = AttackRepertoryofHedgeHog::AttackRepertoryMax;
//	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;
//	m_fatigue_gauge = Gauge_Variable;
//	m_sleep_gauge = Gauge_Variable;
//	m_TimeofBreak = 0;
//	m_IsBreak = false;
//	m_is_delete = false;
//	m_IsHitJudge = false;
//	//	������
//	m_pos.x = 500.0f;
//	m_pos.y = 500.0f;
//	m_speed = 10.0f;
//}
//
//Hedgehog::~Hedgehog()
//{
//
//}
//
//int Hedgehog::GetEnemyPosX()
//{
//	return m_pos.x;
//}
//
//int Hedgehog::GetEnemyPosY()
//{
//	return m_pos.y;
//}
//
//EnemyStateType Hedgehog::GetEnemyState()
//{
//	return m_State;
//}
//
//void Hedgehog::UpdateState()
//{
//	switch (m_State)
//	{
//	case EnemyStateType::Idle:
//
//		EnemyIdle();
//
//		break;
//
//	case EnemyStateType::Break:
//
//		EnemyBreak();
//
//		break;
//
//	case EnemyStateType::Warn:
//
//		EnemyMove();
//
//		break;
//
//	case EnemyStateType::Attack:
//
//		EnemyAttack();
//
//		break;
//
//	case EnemyStateType::Refuge:
//
//		EnemyRefuge();
//
//		break;
//
//	default:
//		/*
//			!!
//		*/
//		break;
//	}
//}
//
//void Hedgehog::ChangeState()
//{
//
//}
//
//void Hedgehog::EnemyMove()
//{
//
//}
//
//void Hedgehog::EnemyRefuge()
//{
//
//}
//
//void Hedgehog::EnemyAttack()
//{
//	/*
//		�G����v���C���[�ւ̏�Ԃɉ����čU�����ύX
//	*/
//
//	switch (m_enemy_to_player_state)
//	{
//	case EnemytoPlayerState::Separated:
//
//		m_attack_repertory = AttackRepertoryofHedgeHog::Rush;
//		Rush();
//		break;
//
//	case EnemytoPlayerState::Close:
//
//		m_attack_repertory = AttackRepertoryofHedgeHog::HeadButt;
//		Headbutt();
//		break;
//
//	case EnemytoPlayerState::Escape:
//
//		m_attack_repertory = AttackRepertoryofHedgeHog::NeedleFire;
//		NeedleFire();
//		break;
//
//	case EnemytoPlayerState::Pursue:
//
//		m_attack_repertory = AttackRepertoryofHedgeHog::None;
//
//		break;
//
//
//	default:
//		/*
//			!!
//		*/
//		break;
//	}
//
//}
//
//void Hedgehog::EnemyIdle()
//{
//
//}
//
//void Hedgehog::EnemyBreak()
//{
//
//}
//
//int Hedgehog::GetSleepGauge()
//{
//	return m_sleep_gauge;
//}
//
//int Hedgehog::GetFatigueGauge()
//{
//	return m_fatigue_gauge;
//}
//
//void Hedgehog::CureSleepiness()
//{
//	m_sleep_gauge += Cure_of_SleepinessPoint;
//}
//
//void Hedgehog::CureFatigue()
//{
//	m_fatigue_gauge += Cure_of_FatiguePoint;
//}
//
//
//
////	�n���l�Y�~Attack�̏����i���j
//
//void Headbutt()
//{
//	/*
//		���˂�����
//		�v���C���[�����ɓ��˂�
//		�������֑f�����ړ����Č��̍��W�܂Ŗ߂�
//		���˂������@150
//	*/
//
//	
//
//
//}
//
//void Rush()
//{
//	/*
//		�ːi����
//		�������x�ő����Ă���
//		�ړ����������߁@800
//	*/
//
//
//
//}
//
//void NeedleFire()
//{
//	/*
//		�Ƃ����ˏ���
//		�Ƃ����˕����@�|���@�v���C���[�̍��W
//		�ǔ��@�Ȃ�
//		���ˁ@3way 2�񂭂炢�H
//	*/
//
//
//
//}
//
