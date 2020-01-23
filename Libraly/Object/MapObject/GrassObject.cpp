#include"GrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include "../../Collision/ShapeType/ShapeRect.h"

GrassObject::GrassObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 1000.0f;
	m_pos.y = P_posYforest - 100;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 205.0f, m_pos.y, 56.0f, 266.0f, 31.0f, 512.0f));
}

void GrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject2));
}