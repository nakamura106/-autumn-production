#pragma once


#include"PlayerBase.h"



class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	 //!< �������֐�
	 void Init()override;
	
	 void SetRectangle()override;

private:
	


	//!< �摜�Ǎ��p�֐�(�Q�[���V�[���ɂׂ������\��)
	void Load()override;


	



	

	int timer;				//���������p

	int timer2;				//Releasenote()�p

	bool m_do_bullet_firing;

	bool m_is_release;

	bool m_do_attack;

	 int notebox[3];
};

