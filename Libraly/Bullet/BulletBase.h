#ifndef BULLETBASE_H_
#define BULLETBASE_H_

#include "../Object/ObjectBase.h"

class BulletBase :public ObjectBase
{
public:
	BulletBase(float x_, float y_, float move_speed_, Direction direction_);
	~BulletBase();
	virtual void Init();
	virtual void Update();
	virtual void Load();
			void Draw();
			void Create() {}

private:
	/*����X�V*/
	void MoveUpdate();

	const float M_BULLET_SYZE = 128.f;
	
	/*�A�j���[�V�����p(�������o)*/
	int m_anim_timer;
	

protected:
	float	m_move_count;		//�ړ���
	float	m_move_limit;		//�ړ�����

};


#endif
