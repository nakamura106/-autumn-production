#include"LargeGrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include"../../Collision/ShapeType/ShapeCircle.h"
#include "../../Collision/ShapeType/ShapeRect.h"


LargeGrassObject::LargeGrassObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 1900.0f;
	m_pos.y = P_posYforest-100;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 137.0f, m_pos.y, 322.0f, 24.0f, 294.0f, 512.0f));

}

void LargeGrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
}