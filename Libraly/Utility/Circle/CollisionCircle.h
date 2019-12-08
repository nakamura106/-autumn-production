#pragma once

#include"../CollisionBase.h"
#include"../../Object/Definition.h"

class CollisionCircle :public CollisionBase
{
public:
	CollisionCircle();
	~CollisionCircle();

	void Init();
	void Update();
	void Arrangement(float centerX, float centerY);
};