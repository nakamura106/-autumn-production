#ifndef BULLETBASE_H_
#define BULLETBASE_H_

#include "../Object/ObjectBase.h"

class BulletBase :public ObjectBase
{
public:
	//注‼：本来は引数にObjectRavelも入れるべきである。改善が必要(メモ日：12/22)
	BulletBase(float x_, float y_, float move_speed_, Direction direction_);
	~BulletBase();
	virtual void Init();
	virtual void Update();
	virtual void Load();
			void Create() {}

private:
	/*動作更新*/
	void MoveUpdate();

	const float M_BULLET_SYZE = 128.f;
	const float M_MOVE_LIMIT_DEFAULT = 1000.f;
	
	/*アニメーション用(仮メンバ)*/
	int m_anim_timer;
	

protected:
	float	m_move_count;		//移動量
	float	m_move_limit;		//移動制限

};


#endif
