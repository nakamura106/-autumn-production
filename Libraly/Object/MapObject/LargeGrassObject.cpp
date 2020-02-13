#include"LargeGrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include"../../Collision/ShapeType/ShapeCircle.h"
#include "../../Collision/ShapeType/ShapeRect.h"


LargeGrassObject::LargeGrassObject()
	:MapObjectBase(211.f, 24.f)
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 1900.0f;
	m_pos.y = P_posYforest-100;
	m_is_p_hit_large_obj = false;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 189.0f, m_pos.y, 211.0f, 294.0f, 24.0f, 1024.0f));
	m_shape_list.push_back(new ShapeRect(m_pos.x, 454.0f, m_pos.y, 47.0f, 315.0f, 33.0f, 1024.0f));

}

void LargeGrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
}