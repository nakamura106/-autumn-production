#ifndef HITEFFECT_H_
#define HITEFFECT_H_

#include "../EffectBase.h"

class HitEffect :public EffectBase
{
public:
	HitEffect(ObjectBase* parent_);
	~HitEffect();

	void Init()override;

	void Update()override;
	
	EffectID GetEffectID()override;
	
private:

};

#endif

