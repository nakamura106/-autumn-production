#include "ShapeCircle.h"

ShapeCircle::ShapeCircle(float x,float y,float radius)
{
	m_CenterX = x;
	m_CenterY = y;
	m_radius = radius;
	m_shape_type = ShapeType::Shape_Circle;
}

ShapeCircle::~ShapeCircle()
{
}
