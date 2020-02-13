
#pragma once

#include"../ObjectBase.h"
#include"MapObjectBase.h"

class LargeGrassObject :public MapObjectBase
{
public:
	LargeGrassObject();
	~LargeGrassObject() {};
	void Init() {};
	
	void Draw();

	//2月14日　田中雑コード　プレイヤーとの当たり判定をするためのコード
	float GetHitObjectPosY() {

		float hit_offset_y = m_hit_offset_y;

		if (m_is_p_hit_large_obj == true) {
			hit_offset_y = 47.f;
		}

		return m_pos.y + hit_offset_y - (m_hit_side_y / 2.f);
	}
	void HitAction(ObjectRavel ravel_, float hit_use_atk_) {
		if (ravel_ == ObjectRavel::Ravel_Player && hit_use_atk_ == 1.f) {
			m_is_p_hit_large_obj = true;
		}
		else {
			m_is_p_hit_large_obj = false;
		}
	}

private:
	bool m_is_p_hit_large_obj;


};