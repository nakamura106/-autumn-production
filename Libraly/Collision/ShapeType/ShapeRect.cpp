#include "ShapeRect.h"

ShapeRect::ShapeRect(float x,float y,float side_x,float side_y)
{
	m_CenterX = x;
	m_CenterY = y;
	m_side_x = side_x;
	m_side_y = side_y;
	m_shape_type = ShapeType::Shape_Rect;
}

ShapeRect::~ShapeRect()
{
}
