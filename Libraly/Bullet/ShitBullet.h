#pragma once
#include"EnemyBullet.h"

class ShitBullet :public EnemyBullet {
public:
	ShitBullet(
		float x_,
		float y_,
		float move_speed_x_,
		float move_speed_y_,
		float acceleration,
		Direction direction_,
		GameCategoryTextureList use_tex_ = GameCategoryTextureList::GameEnemy_Bullet_Shit,
		int tex_split_w_ = 1,
		int tex_split_h_ = 1,
		int tex_split_all = 1
	);

	virtual void MoveUpdate();

private:
	const int	M_DELETE_TIME		= 300;		//���ł���܂ł̎���
	int		m_savetime_delete;	//�t���[�����i�[�F���ł���܂ł̎��Ԃ𑪒�
	float	m_acceleration;		//�����x

protected:
	bool	m_is_dropdown;		//�n�ʂɗ����Ă����Ԃ̏ꍇ�Atrue�ɂȂ�

};