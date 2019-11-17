#pragma once

#include"../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	virtual void Init();
	virtual void Create();
	virtual void Update();
	virtual void Draw();

protected:
	float m_sleep_gauge;	//–°‚èƒQ[ƒW
	float m_fatigue_gsuge;	//”æ˜JƒQ[ƒW
	

};
