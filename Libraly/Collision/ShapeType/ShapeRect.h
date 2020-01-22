#ifndef SHAPERECT_H_
#define SHAPERECT_H_

#include "../ShapeBase.h"

class ShapeRect :public ShapeBase
{
public:
	ShapeRect(float x, float offset_x, float y, float offset_y, float side_x, float side_y, float tex_x);
	~ShapeRect()override;

	ShapeType GetShapeType()const override { return m_shape_type; }

};

#endif

