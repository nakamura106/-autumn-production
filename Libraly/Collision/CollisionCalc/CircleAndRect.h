#ifndef CIRCLEANDRECT_H_
#define CIRCLEANDRECT_H_

#include "CollisionBase.h"

class CircleAndRect :public CollisionBase
{
public:
	CircleAndRect();
	~CircleAndRect()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;

};

#endif

