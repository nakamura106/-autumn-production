#ifndef DEBUFFEFFECT_H_
#define DEBUFFEFFECT_H_

#include "../EffectBase.h"

class DebuffEffect :public EffectBase
{
public:
	DebuffEffect();
	~DebuffEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif
