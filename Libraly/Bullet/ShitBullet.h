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
	const int	M_DELETE_TIME		= 300;		//消滅するまでの時間
	int		m_savetime_delete;	//フレーム数格納：消滅するまでの時間を測定
	float	m_acceleration;		//加速度

protected:
	bool	m_is_dropdown;		//地面に落ちている状態の場合、trueになる

};