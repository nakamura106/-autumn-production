#ifndef SWEATEFFECT_H_
#define SWEATEFFECT_H_

#include "../EffectBase.h"

class SweatEffect :public EffectBase
{
public:
	SweatEffect(ObjectBase* parent_);
	~SweatEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:

};

#endif

