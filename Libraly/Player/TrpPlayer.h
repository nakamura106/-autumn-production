#pragma once

#pragma once

#include"PlayerBase.h"


class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	//!< �������֐�
	 void Init()override;
	 //!< �摜�Ǎ��p�֐�(�Q�[���V�[���ɂׂ������\��)
	 void Load()override;
	 //!< �A�b�v�f�[�g�֐�(�����X�V�p)
	 void Update()override;
	 //!< �`��֐�(�I�u�W�F�N�g�x�[�X�ł܂Ƃ߂Ă��\��)
	 void Draw()override;
	 //!< �v���C���[�R���g���[���֐�(�v���C���[�̑���)
	 void P_Controll()override;
	 //!< �A�j���[�V�����̏������֐�
	 void InitAnimation()override;
	 //!< �A�j���[�V�����̕`��֐�(�摜���A�j���[�V���������邽�߂̊֐�)
	 void DrawAnimation()override;
	 //!< �A�j���[�V�����̃A�b�v�f�[�g�֐�(��Ԃɂ���ăA�j���[�V������ς���֐� ��DrawAnimation�Ɠ����\��)
	 void UpdateAnimation()override;
	 //!< �v���C���[�̃W�����v�����֐�
	 void Jump()override;
	 //!< �e���˒������𒴂����特���X�g�b�N�������֐�
	 void ReleaseNote()override;
	 //!< �摜���Ăяo���ĕϐ�(Draw�Ŏg��)�Ɋi�[����֐�
	 void GetMotion(int Llist,int Rlist);
	 //!< ���݂̍��W��n���֐�
	 Position GetPos()override;

private:
	
};

