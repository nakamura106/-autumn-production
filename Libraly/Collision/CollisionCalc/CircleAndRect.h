#ifndef CIRCLEANDRECT_H_
#define CIRCLEANDRECT_H_

#include "CollisionBase.h"

class CircleAndRect :public CollisionBase
{
public:
	CircleAndRect();
	~CircleAndRect()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;


private:
	float m_circle_centerX, m_circle_centerY;
	float m_circle_radius;

	float m_rect_centerX, m_rect_centerY;
	float m_rect_width, m_rect_height;

	float m_sumX, m_sumY;
};

#endif

