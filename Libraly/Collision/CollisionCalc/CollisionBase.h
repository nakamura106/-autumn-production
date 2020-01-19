#ifndef COLLISIONBASE_H_
#define COLLISIONBASE_H_

#include "../../Object/Definition.h"
#include "../ShapeBase.h"


class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();

	// �����蔻��v�Z�֐�
	virtual bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2) = 0;

};

#endif


