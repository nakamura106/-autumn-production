#include "ShapeBase.h"
#include "../Manager/ObjectManager.h"

ShapeBase::ShapeBase()
{
	m_shape_type = ShapeType::ShapeTypeNon;

	m_CenterX = 0.f;
	m_CenterY = 0.f;
	m_side_x = 0.f;
	m_side_y = 0.f;
	m_radius = 0.f;
	m_offset_x = 0.f;
	m_offset_y = 0.f;
	m_tex_x = 0.f;
}

ShapeBase::~ShapeBase()
{
}

void ShapeBase::Update(float x, float y, int direction)
{
	m_direction = direction;

	if (m_direction == Direction::RIGHT)
	{
		m_CenterX = x + m_offset_x;
	}
	else if(m_direction == Direction::LEFT){
		m_CenterX = x + m_tex_x - m_offset_x;
	}
	m_CenterY = y + m_offset_y;

	
}


