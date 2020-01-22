#include"BananaObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"

BananaObject::BananaObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 500.0f;
	m_pos.y = P_posYforest;
	
}

void BananaObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
}