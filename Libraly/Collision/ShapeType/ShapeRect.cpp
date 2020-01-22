#include "ShapeRect.h"

ShapeRect::ShapeRect(float x,float offset_x, float y, float offset_y, float side_x,float side_y, float tex_x)
{
	m_CenterX = x;
	m_offset_x = offset_x;
	m_CenterY = y;
	m_offset_y = offset_y;
	m_side_x = side_x;
	m_side_y = side_y;
	m_tex_x = tex_x;
	m_shape_type = ShapeType::Shape_Rect;
}

ShapeRect::~ShapeRect()
{
}
