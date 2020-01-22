#include "CircleAndRect.h"

CircleAndRect::CircleAndRect()
{
	m_circle_centerX = 0.f;
	m_circle_centerY = 0.f;
	m_circle_radius = 0.f;

	m_rect_centerX = 0.f;
	m_rect_centerY = 0.f;
	m_rect_halfX = 0.f;
	m_rect_halfY = 0.f;

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
		m_rect_halfX = shape2.GetSideX() / 2.0f;
		m_rect_halfY = shape2.GetSideY() / 2.0f;
	}
	else
	{
		m_circle_centerX = shape2.GetCenterX();
		m_circle_centerY = shape2.GetCenterY();
		m_circle_radius = shape2.GetRadius();

		m_rect_centerX = shape1.GetCenterX();
		m_rect_centerY = shape1.GetCenterY();
		m_rect_halfX = shape1.GetSideX() / 2.0f;
		m_rect_halfY = shape1.GetSideY() / 2.0f;
	}

	m_sumX = m_circle_centerX - m_rect_centerX;
	m_sumY = m_circle_centerY - m_rect_centerY;
	if (m_sumX < 0.f)
	{
		m_sumX *= -1.0f;
	}
	if (m_sumY < 0.f)
	{
		m_sumY *= -1.0f;
	}


	if (m_sumX <= m_circle_radius + m_rect_halfX)
	{
		if (m_sumY <= m_circle_radius + m_rect_halfY)
		{
			return true;
		}
	}
	else
	{
		return false;
	}

}
