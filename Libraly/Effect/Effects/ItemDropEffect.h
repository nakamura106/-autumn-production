#ifndef ITEMDROPEFFECT_H_
#define ITEMDROPEFFECT_H_

#include "../EffectBase.h"

class ItemDropEffect :public EffectBase
{
public:
	ItemDropEffect();
	~ItemDropEffect();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif
