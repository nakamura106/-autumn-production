#include "ShapeCircle.h"

ShapeCircle::ShapeCircle(float x,float offset_x, float y, float offset_y, float radius)
{
	m_CenterX = x;
	m_offset_x = offset_x;
	m_CenterY = y;
	m_offset_y = offset_y;
	m_radius = radius;
	m_shape_type = ShapeType::Shape_Circle;
}

ShapeCircle::~ShapeCircle()
{
}
