#ifndef DIEEFFECT_H_
#define DIEEFFECT_H_

#include "../EffectBase.h"

class DieEffect :public EffectBase
{
public:
	DieEffect(ObjectBase* parent_);
	~DieEffect();

	void Init()override;
	void Update()override;

	EffectID GetEffectID()override;

private:

};

#endif

