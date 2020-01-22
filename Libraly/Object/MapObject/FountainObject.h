#pragma once

#include"../ObjectBase.h"
#include"MapObjectBase.h"

class FountainObject :public MapObjectBase
{
public:
	FountainObject();
	~FountainObject() {};
	void Init() {};
	void Load() {};

	void Draw();


};