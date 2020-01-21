#include "CircleAndCircle.h"
#include <math.h>

CircleAndCircle::CircleAndCircle()
{
	m_circle1_centerX = 0.f;
	m_circle1_centerY = 0.f;
	m_circle1_radius = 0.f;

	m_circle2_centerX = 0.f;
	m_circle2_centerY = 0.f;
	m_circle2_radius = 0.f;

	m_sumX = 0.f;
	m_sumY = 0.f;
	m_distance = 0.f;
}

CircleAndCircle::~CircleAndCircle()
{
}

bool CircleAndCircle::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	m_circle1_radius = shape1.GetRadius();
	m_circle1_centerX = shape1.GetCenterX();
	m_circle1_centerY = shape1.GetCenterY();
	
	m_circle2_radius = shape2.GetRadius();
	m_circle2_centerX = shape1.GetCenterX();
	m_circle2_centerY = shape1.GetCenterY();

	m_sumX = m_circle1_centerX - m_circle2_centerX;
	m_sumY = m_circle1_centerY - m_circle2_centerY;

	m_distance = sqrtf(m_sumX * m_sumX + m_sumY * m_sumY);

	if (m_distance <= m_circle1_radius + m_circle2_radius)
	{
		return true;
	}
	else
	{
		return false;
	}

}
