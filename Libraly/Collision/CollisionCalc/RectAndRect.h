#ifndef RECTANDRECT_H_
#define RECTANDRECT_H_

#include "CollisionBase.h"

class RectAndRect :public CollisionBase
{
public:
	RectAndRect();
	~RectAndRect()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;

};

#endif

