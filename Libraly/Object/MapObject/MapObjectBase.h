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

	void CollisionParamUpdate()override;

	virtual float GetHitUseAtk(ObjectRavel hit_obj_) {

		if (hit_obj_ == ObjectRavel::Ravel_Player) {
			return m_pos.y;
		}

		return m_hit_use_atk;
	}

private:
	
};