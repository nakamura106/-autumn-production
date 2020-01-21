#ifndef RECTANDRECT_H_
#define RECTANDRECT_H_

#include "CollisionBase.h"

class RectAndRect :public CollisionBase
{
public:
	RectAndRect();
	~RectAndRect()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;

private:
	float m_rect1_centerX, m_rect1_centerY;
	float m_rect1_halfX, m_rect1_halfY;

	float m_rect2_centerX, m_rect2_centerY;
	float m_rect2_halfX, m_rect2_halfY;

	float m_sum_x, m_sum_y;

};

#endif

