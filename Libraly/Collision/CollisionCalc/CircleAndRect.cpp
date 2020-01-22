#include "CircleAndRect.h"
#include <math.h>

CircleAndRect::CircleAndRect()
{
	m_circle_centerX = 0.f;
	m_circle_centerY = 0.f;
	m_circle_radius = 0.f;

	m_rect_centerX = 0.f;
	m_rect_centerY = 0.f;
	m_rect_width = 0.f;
	m_rect_height = 0.f;

	m_sumX = 0.f;
	m_sumY = 0.f;
}

CircleAndRect::~CircleAndRect()
{
}

bool CircleAndRect::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	if (shape1.GetShapeType() == ShapeType::Shape_Circle)
	{
		m_circle_centerX = shape1.GetCenterX();
		m_circle_centerY = shape1.GetCenterY();
		m_circle_radius = shape1.GetRadius();

		m_rect_centerX = shape2.GetCenterX();
		m_rect_centerY = shape2.GetCenterY();
		m_rect_width = shape2.GetSideX();
		m_rect_height = shape2.GetSideY();
	}
	else if (shape1.GetShapeType() == ShapeType::Shape_Rect)
	{
		m_circle_centerX = shape2.GetCenterX();
		m_circle_centerY = shape2.GetCenterY();
		m_circle_radius = shape2.GetRadius();

		m_rect_centerX = shape1.GetCenterX();
		m_rect_centerY = shape1.GetCenterY();
		m_rect_width = shape1.GetSideX();
		m_rect_height = shape1.GetSideY();
	}

	// 第1矩形の当たり判定
	float col_rect_left_x = m_rect_centerX - (m_rect_width / 2.0f) - m_circle_radius;
	float col_rect_right_x = col_rect_left_x + (m_circle_radius * 2.0f) + m_rect_width;
	float col_rect_up_y = m_rect_centerY - (m_rect_height / 2.0f);
	float col_rect_down_y = col_rect_up_y + m_rect_height;

	if (col_rect_left_x <= m_circle_centerX &&
		m_circle_centerX <= col_rect_right_x &&
		col_rect_up_y <= m_circle_centerY &&
		m_circle_centerY <= col_rect_down_y)
	{
		return true;
	}

	// 第2矩形の当たり判定
	col_rect_left_x = m_rect_centerX - (m_rect_width / 2.0f);
	col_rect_right_x = col_rect_left_x + m_rect_width;
	col_rect_up_y = m_rect_centerY - (m_rect_height / 2.0f) - m_circle_radius;
	col_rect_down_y = col_rect_up_y + (m_circle_radius * 2.0f) + m_rect_height;

	if (col_rect_left_x <= m_circle_centerX &&
		m_circle_centerX <= col_rect_right_x &&
		col_rect_up_y <= m_circle_centerY &&
		m_circle_centerY <= col_rect_down_y)
	{
		return true;
	}

	// 各頂点当たり判定
	float col_vertex_x = m_rect_centerX - (m_rect_width / 2.0f);
	float col_vertex_y = m_rect_centerY - (m_rect_height / 2.0f);

	m_sumX = col_vertex_x - m_circle_centerX;
	m_sumY = col_vertex_y - m_circle_centerY;

	if (m_circle_radius >= sqrtf(m_sumX * m_sumX + m_sumY * m_sumY))
	{
		return true;
	}

	col_vertex_x += m_rect_width;
	m_sumX = col_vertex_x - m_circle_centerX;
	if (m_circle_radius >= sqrtf(m_sumX * m_sumX + m_sumY * m_sumY))
	{
		return true;
	}

	col_vertex_y += m_rect_height;
	m_sumY = col_vertex_y - m_circle_centerY;
	if (m_circle_radius >= sqrtf(m_sumX * m_sumX + m_sumY * m_sumY))
	{
		return true;
	}

	col_vertex_x -= m_rect_width;
	m_sumX = col_vertex_x - m_circle_centerX;
	if (m_circle_radius >= sqrtf(m_sumX * m_sumX + m_sumY * m_sumY))
	{
		return true;
	}

	return false;

}
