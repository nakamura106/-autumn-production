#pragma once
#include"../ObjectBase.h"

class MapObjectBase :public ObjectBase
{
public:
	MapObjectBase();
	~MapObjectBase() {};
	void Init() {};
	void Load() {};

	void Update();

	void MoveUpdate(Direction direction_);

	void CollisionParamUpdate()override;

private:
	
};