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
}

ShapeBase::~ShapeBase()
{
}

void ShapeBase::Update(float x, float y)
{
	m_CenterX = x;
	m_CenterY = y;
}


