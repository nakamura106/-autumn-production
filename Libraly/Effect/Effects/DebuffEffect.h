#ifndef DEBUFFEFFECT_H_
#define DEBUFFEFFECT_H_

#include "../EffectBase.h"

class DebuffEffect :public EffectBase
{
public:
	DebuffEffect(ObjectBase* parent_);
	~DebuffEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:

};

#endif

