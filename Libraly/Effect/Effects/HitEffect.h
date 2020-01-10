#ifndef HITEFFECT_H_
#define HITEFFECT_H_

#include "../EffectBase.h"

class HitEffect :public EffectBase
{
public:
	HitEffect();
	~HitEffect();

	void Init()override;
	void Update()override;
	void Draw()override;
	
private:

};

#endif

