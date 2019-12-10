#pragma once


#include"PlayerBase.h"



class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	 //!< �������֐�
	 void Init()override;
	 //!< �A�b�v�f�[�g�֐�(�����X�V�p)
	 void Update()override;
	 //!< �`��֐�(�I�u�W�F�N�g�x�[�X�ł܂Ƃ߂Ă��\��)
	 void Draw()override;

	 void SetRectangle()override;

private:
	//!< �v���C���[�̃W�����v�����֐�
	void Jump()override;
	//!< �摜���Ăяo���ĕϐ�(Draw�Ŏg��)�Ɋi�[����֐�
	void GetMotion(int Llist, int Rlist);
	//!< �A�j���[�V�����̃A�b�v�f�[�g�֐�(��Ԃɂ���ăA�j���[�V������ς���֐� ��DrawAnimation�Ɠ����\��)
	void UpdateAnimation()override;
	//!< �e���˒������𒴂����特���X�g�b�N�������֐�
	void ReleaseNote()override;
	//!< �A�j���[�V�����̕`��֐�(�摜���A�j���[�V���������邽�߂̊֐�)
	void DrawAnimation()override;
	//!< �A�j���[�V�����̏������֐�
	void InitAnimation()override;
	//!< �v���C���[�R���g���[���֐�(�v���C���[�̑���)
	void P_Controll()override;
	//!< �摜�Ǎ��p�֐�(�Q�[���V�[���ɂׂ������\��)
	void Load()override;

	void Attack();

	void CreateBullets(PlayerBulletType bullettype)override;


	int atkjudge();

	void Drawatk();

	int timer;				//���������p

	int timer2;				//Releasenote()�p

	bool m_do_bullet_firing;

	bool m_is_release;

	bool m_do_attack;

	 int notebox[3];
};

