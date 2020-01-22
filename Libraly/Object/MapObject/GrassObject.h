#pragma once

#include"../ObjectBase.h"
#include"MapObjectBase.h"

class GrassObject :public MapObjectBase
{
public:
	GrassObject();
	~GrassObject() {};
	void Init() {};
	void Load() {};

	void Draw();


};