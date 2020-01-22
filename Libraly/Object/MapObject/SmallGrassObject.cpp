#include"SmallGrassObject.h"
#include"../../Engine/Graphics.h"
#include"../../Object/Definition.h"

SmallGrassObject::SmallGrassObject()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 400.0f;
	m_pos.y = P_posYforest;

}

void SmallGrassObject::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
}