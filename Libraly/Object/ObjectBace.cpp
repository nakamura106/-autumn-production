#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
	m_speed = 0.0f;
	m_is_delete = false;
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Draw()
{
	// 各メンバ変数の値は派生クラス内で指定すること
	DrawUVScrollTexture(m_pos.x, m_pos.y, GetTexture(m_draw_param.category_id, m_draw_param.texture_id), m_draw_param.tu, m_draw_param.tv);
}
 