#ifndef LANDINGEFFECT_H_
#define LANDINGEFFECT_H_

#include "../EffectBase.h"

class LandingEffect :public EffectBase
{
public:
	LandingEffect(ObjectBase* parent_);
	~LandingEffect();

	void Init()override;
	
	EffectID GetEffectID()override;

private:

};

#endif
