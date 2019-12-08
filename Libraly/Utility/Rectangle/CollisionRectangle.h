#pragma once

#include"../CollisionBase.h"
#include"../../Object/Definition.h"

class CollisionRectangle :public CollisionBase
{
public:
	CollisionRectangle();
	~CollisionRectangle();

	void Init();
	void Update();
	void Arrangement(float centerX, float centerY);
};
