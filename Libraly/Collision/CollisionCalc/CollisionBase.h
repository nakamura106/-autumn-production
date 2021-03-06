#ifndef COLLISIONBASE_H_
#define COLLISIONBASE_H_

#include "../../Object/Definition.h"
#include "../ShapeBase.h"


class CollisionBase
{
public:
	CollisionBase();
	virtual ~CollisionBase();
	
	// 当たり判定計算関数
	virtual bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2) = 0;

};



#endif


