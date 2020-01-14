#ifndef DIEEFFECT_H_
#define DIEEFFECT_H_

#include "../EffectBase.h"

class DieEffect :public EffectBase
{
public:
	DieEffect();
	~DieEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:

};

#endif

