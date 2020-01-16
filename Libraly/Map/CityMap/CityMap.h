#pragma once
#include"../Map.h"

class CityMap :public Map
{
	void Load()override;
	void Draw()override;
};

class CityFg :public Fg
{
	void Load()override;
	void Draw()override;
};

