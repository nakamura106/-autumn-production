#ifndef ANYCOLLISION_H_
#define ANYCOLLISION_H_

#include "CollisionBase.h"

class AnyCollision :public CollisionBase
{
public:
	AnyCollision();
	~AnyCollision()override;

	bool CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)override;

private:
	CollisionBase* m_collision_table[static_cast<unsigned int>(ShapeType::ShapeTypeMax)][static_cast<unsigned int>(ShapeType::ShapeTypeMax)];


};

#endif

