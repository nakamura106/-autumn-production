#include"LargeGrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"

LargeGrassObject::LargeGrassObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 1900.0f;
	m_pos.y = P_posYforest-100;

}

void LargeGrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
}