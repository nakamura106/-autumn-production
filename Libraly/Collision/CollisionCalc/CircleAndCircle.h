#ifndef CIRCLEANDCIRCLE_H_
#define CIRCLEANDCIRCLE_H_

#include "CollisionBase.h"

class CircleAndCircle :public CollisionBase
{
public:
	CircleAndCircle();
	~CircleAndCircle()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;
};

#endif

