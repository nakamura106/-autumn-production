#ifndef SLEEPEFFECT_H_
#define SLEEPEFFECT_H_

#include "../EffectBase.h"

class SleepEffect :public EffectBase
{
public:
	SleepEffect();
	~SleepEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:

};

#endif

