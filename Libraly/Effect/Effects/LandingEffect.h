#ifndef LANDINGEFFECT_H_
#define LANDINGEFFECT_H_

#include "../EffectBase.h"

class LandingEffect :public EffectBase
{
public:
	LandingEffect();
	~LandingEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:

};

#endif
