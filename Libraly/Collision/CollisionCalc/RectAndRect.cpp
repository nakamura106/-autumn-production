#include "RectAndRect.h"
#include <math.h>

RectAndRect::RectAndRect()
{
	m_rect1_centerX = 0.f;
	m_rect1_centerY = 0.f;
	m_rect1_halfX = 0.f;
	m_rect1_halfY = 0.f;

	m_rect2_centerX = 0.f;
	m_rect2_centerY = 0.f;
	m_rect2_halfX = 0.f;
	m_rect2_halfY = 0.f;

	m_sum_x = 0.f;
	m_sum_y = 0.f;
}

RectAndRect::~RectAndRect()
{
}

bool RectAndRect::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	m_rect1_centerX = shape1.GetCenterX();
	m_rect1_centerY = shape1.GetCenterY();
	m_rect1_halfX = shape1.GetSideX() / 2.0f;
	m_rect1_halfY = shape1.GetSideY() / 2.0f;
	
	m_rect2_centerX = shape2.GetCenterX();
	m_rect2_centerY = shape2.GetCenterY();
	m_rect2_halfX = shape2.GetSideX() / 2.0f;
	m_rect2_halfY = shape2.GetSideY() / 2.0f;

	m_sum_x = m_rect1_centerX - m_rect2_centerX;
	m_sum_y = m_rect1_centerY - m_rect2_centerY;
	if (m_sum_x < 0.f)
	{
		m_sum_x *= -1.0f;
	}
	if (m_sum_y < 0.f)
	{
		m_sum_y *= -1.0f;
	}
	
	if (m_sum_x <= m_rect1_halfX + m_rect2_halfX)
	{
		if (m_sum_y <= m_rect1_halfY + m_rect2_halfY)
		{
			return true;
		}
	}


	return false;

}
