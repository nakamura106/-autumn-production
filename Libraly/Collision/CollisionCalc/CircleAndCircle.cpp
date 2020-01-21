#include "CircleAndCircle.h"
#include <math.h>

CircleAndCircle::CircleAndCircle()
{
}

CircleAndCircle::~CircleAndCircle()
{
}

bool CircleAndCircle::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	float circle1_radius = shape1.GetRadius();
	float circle1_centerX = shape1.GetCenterX();
	float circle1_centerY = shape1.GetCenterY();

	float circle2_radius = shape2.GetRadius();
	float circle2_centerX = shape1.GetCenterX();
	float circle2_centerY = shape1.GetCenterY();

	float a = circle1_centerX - circle2_centerX;
	float b = circle1_centerY - circle2_centerY;

	float c = sqrt(a * a + b * b);

	if (c <= circle1_radius + circle2_radius)
	{
		return true;
	}
	else
	{
		return false;
	}

}
