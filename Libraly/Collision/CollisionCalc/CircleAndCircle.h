#ifndef CIRCLEANDCIRCLE_H_
#define CIRCLEANDCIRCLE_H_

#include "CollisionBase.h"

class CircleAndCircle :public CollisionBase
{
public:
	CircleAndCircle();
	~CircleAndCircle()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;

private:
	float m_circle1_centerX, m_circle1_centerY;
	float m_circle1_radius;

	float m_circle2_centerX, m_circle2_centerY;
	float m_circle2_radius;

	float m_sumX, m_sumY;
	float m_distance;
};

#endif

