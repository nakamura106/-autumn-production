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
	// �e�����o�ϐ��̒l�͔h���N���X���Ŏw�肷�邱��
	DrawUVScrollTexture(m_pos.x, m_pos.y, GetTexture(m_draw_param.category_id, m_draw_param.texture_id), m_draw_param.tu, m_draw_param.tv);
}
 