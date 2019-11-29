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
	/*アニメーション更新*/
	void AnimationUpdate();
	/*動作更新*/
	void MoveUpdate();

	const float M_BULLET_SYZE = 128.f;
	
	/*アニメーション用(仮メンバ)*/
	int m_anim_timer;
	

protected:
	/*アニメーション用(仮メンバ)*/
	//将来的にはObjectbaseに欲しい
	int		m_anim_flame;		//切り替えフレーム数
	int		m_anim_tex_width;	//横分割数
	int		m_anim_tex_height;	//縦分割数
	int		m_anim_tex_all;		//分割総数

	float	m_move_count;		//移動量
	float	m_move_limit;		//移動制限

};


#endif
