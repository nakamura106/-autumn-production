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
	DrawUVScrollTexture(m_param.x, m_param.y, GetTexture(m_param.category_id, m_param.texture_id), m_param.tu, m_param.tv);
}
 