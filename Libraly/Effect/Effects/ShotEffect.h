#ifndef SHOTEFFECT_H_
#define SHOTEFFECT_H_

#include "../EffectBase.h"

class ShotEffect :public EffectBase
{
public:
	ShotEffect(ObjectBase* parent_);
	~ShotEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

	EffectID GetEffectID()override;

private:


};

#endif

