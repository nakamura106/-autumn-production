#include"BananaObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"
#include "../../Collision/ShapeType/ShapeRect.h"

BananaObject::BananaObject()
	:MapObjectBase(51.f,22.f)
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 500.0f;
	m_pos.y = P_posYforest;
	
	m_shape_list.push_back(new ShapeRect(m_pos.x, 227.0f, m_pos.y, 51.0f, 225.0f, 22.0f, 512.0f));
}

void BananaObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
}