#include"SmallGrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include "../../Collision/ShapeType/ShapeRect.h"

SmallGrassObject::SmallGrassObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 400.0f;
	m_pos.y = P_posYforest;

	m_shape_list.push_back(new ShapeRect(m_pos.x, 136.0f, m_pos.y, 92.0f, 264.0f, 31.0f, 512.0f));
}

void SmallGrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
}