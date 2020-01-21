#include "RectAndRect.h"

RectAndRect::RectAndRect()
{
}

RectAndRect::~RectAndRect()
{
}

bool RectAndRect::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	float rect1_CenterX = shape1.GetCenterX();
	float rect1_CenterY = shape1.GetCenterY();
	float rect1_sideX = shape1.GetSideX();
	float rect1_sideY = shape1.GetSideY();
	
	float rect2_CenterX = shape2.GetCenterX();
	float rect2_CenterY = shape2.GetCenterY();
	float rect2_sideX = shape2.GetSideX();
	float rect2_sideY = shape2.GetSideY();

	

}
