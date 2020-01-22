#ifndef SHAPECIRCLE_H_
#define SHAPECIRCLE_H_

#include "../ShapeBase.h"

class ShapeCircle :public ShapeBase
{
public:
	ShapeCircle(float x, float offset_x, float y, float offset_y, float radius, float tex_x);
	~ShapeCircle()override;

	ShapeType GetShapeType()const override { return m_shape_type; }

};

#endif

