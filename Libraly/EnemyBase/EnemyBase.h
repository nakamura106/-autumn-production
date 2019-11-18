#pragma once

#include"../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	virtual void Init()=0;
	virtual void Create()=0;
	virtual void Update()=0;
	virtual void Draw()=0;

protected:
	float m_sleep_gauge;	//–°‚èƒQ[ƒW
	float m_fatigue_gsuge;	//”æ˜JƒQ[ƒW
	

};
