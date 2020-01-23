#pragma once
#include"../ObjectBase.h"

class MapObjectBase :public ObjectBase
{
public:
	MapObjectBase();
	~MapObjectBase() {};
	void Init() {};
	

	void Update();

	void MoveUpdate(Direction direction_);

private:
	
};