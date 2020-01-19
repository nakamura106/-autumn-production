#ifndef SHAPECIRCLE_H_
#define SHAPECIRCLE_H_

#include "../ShapeBase.h"

class ShapeCircle :public ShapeBase
{
public:
	ShapeCircle(float x,float y,float radius);
	~ShapeCircle()override;

	ShapeType GetShapeType()const override { return m_shape_type; }
	
	float GetRadius() { return m_radius; }

private:
	float m_radius;	// ”¼Œa

};

#endif

