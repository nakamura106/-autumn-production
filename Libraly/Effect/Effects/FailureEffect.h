#ifndef FAILUREEFFECT_H_
#define FAILUREEFFECT_H_

#include "../EffectBase.h"

class FailureEffect :public EffectBase
{
public:
	FailureEffect();
	~FailureEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif

