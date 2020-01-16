#ifndef FAILUREEFFECT_H_
#define FAILUREEFFECT_H_

#include "../EffectBase.h"

class FailureEffect :public EffectBase
{
public:
	FailureEffect(ObjectBase* parent_);
	~FailureEffect();

	void Init()override;

	EffectID GetEffectID()override;

private:

};

#endif

