#pragma once
#include"../Map.h"

class SeaMap :public Map
{
	void Load()override;
	void Draw()override;
};

class SeaFg :public Fg
{
	void Load()override;
	void Draw()override;
};
