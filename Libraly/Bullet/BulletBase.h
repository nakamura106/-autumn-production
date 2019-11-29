#ifndef BULLETBASE_H_
#define BULLETBASE_H_

#include "../Object/ObjectBase.h"

class BulletBase :public ObjectBase
{
public:
	BulletBase();
	~BulletBase();
	virtual void Init();
	virtual void Update();
	virtual void Load();
			void Draw();
			void Create() {}

private:
	/*�A�j���[�V�����X�V*/
	void AnimationUpdate();
	/*����X�V*/
	void MoveUpdate();

	const float M_BULLET_SYZE = 128.f;
	
	/*�A�j���[�V�����p(�������o)*/
	int m_anim_timer;
	

protected:
	/*�A�j���[�V�����p(�������o)*/
	//�����I�ɂ�Objectbase�ɗ~����
	int		m_anim_flame;		//�؂�ւ��t���[����
	int		m_anim_tex_width;	//��������
	int		m_anim_tex_height;	//�c������
	int		m_anim_tex_all;		//��������

	float	m_move_count;		//�ړ���
	float	m_move_limit;		//�ړ�����

};


#endif
