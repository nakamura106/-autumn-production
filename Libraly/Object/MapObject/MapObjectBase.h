#pragma once
#include"../ObjectBase.h"

class MapObjectBase :public ObjectBase
{
public:
	MapObjectBase(float hit_offset_y_, float hit_side_y_);
	~MapObjectBase() {};
	void Init() {};
	
	void Update();

	void MoveUpdate(Direction direction_);

	void CollisionParamUpdate()override;

	virtual float GetHitUseAtk(ObjectRavel hit_obj_) {

		if (hit_obj_ == ObjectRavel::Ravel_Player) {
			return GetHitObjectPosY();
		}

		return m_hit_use_atk;
	}

	virtual float GetHitObjectPosY() {
		return m_pos.y + m_hit_offset_y - (m_hit_side_y / 2.f);
	}

protected:
	float m_hit_offset_y;
	float m_hit_side_y;
	
};