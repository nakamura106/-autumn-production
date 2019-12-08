#pragma once

#include"../CollisionBase.h"
#include"../../Object/Definition.h"

class CollisionLine :public CollisionBase
{
public:
	CollisionLine();
	~CollisionLine();

	void Init();
	void Update();
	void Arrangement(float centerX, float centerY);
};