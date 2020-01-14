#ifndef SLEEPEFFECT_H_
#define SLEEPEFFECT_H_

#include "../EffectBase.h"

class SleepEffect :public EffectBase
{
public:
	SleepEffect(ObjectBase* parent_);
	~SleepEffect();

	void Init()override;
	void Update()override;
	
	EffectID GetEffectID()override;

private:

};

#endif

