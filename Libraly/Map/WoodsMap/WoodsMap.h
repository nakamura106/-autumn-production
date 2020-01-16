#pragma once
#include"../Map.h"

class WoodsMap :public Map
{
	void Load()override;
	void Draw()override;
};

class WoodsFg :public Fg
{
	void Load()override;
	void Draw()override;
};