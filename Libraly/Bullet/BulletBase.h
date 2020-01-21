#ifndef BULLETBASE_H_
#define BULLETBASE_H_

#include "../Object/ObjectBase.h"

class BulletBase :public ObjectBase
{
public:
	//注‼：本来は引数にObjectRavelも入れるべきである。改善が必要(メモ日：12/22)
	BulletBase(
		float x_, 
		float y_, 
		float move_speed_, 
		Direction direction_, 
		ObjectRavel obj_ravel_, 
		float speed_y_ = 0.f, 
		int draw_angle_ = 0,
		int tex_size = 128.f
	);
	~BulletBase();
	virtual void Init();
	virtual void Update();
	virtual void Load();
			void Create() {}

private:
	const float M_MOVE_LIMIT_DEFAULT = 1000.f;
	
	/*アニメーション用(仮メンバ)*/
	int m_anim_timer;
	

protected:
	/*動作更新*/
	virtual void MoveUpdate();

	float	m_move_count;		//移動量
	float	m_move_limit;		//移動制限
	float	m_speed_y;			//y軸移動
	const float M_BULLET_SYZE = 128.f;

};


#endif
