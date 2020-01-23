#include"FountainObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include "../../Collision/ShapeType/ShapeRect.h"

FountainObject::FountainObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 1900.0f;
	m_pos.y = P_posYforest-200;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 203.0f, m_pos.y, 34.0f, 336.0f, 30.0f, 512.0f));
}

void FountainObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject2));
}