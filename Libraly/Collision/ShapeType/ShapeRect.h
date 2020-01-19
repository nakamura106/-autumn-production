#ifndef SHAPERECT_H_
#define SHAPERECT_H_

#include "../ShapeBase.h"

class ShapeRect :public ShapeBase
{
public:
	ShapeRect(float x,float y,float side_x,float side_y);
	~ShapeRect()override;

	ShapeType GetShapeType()const override { return m_shape_type; }

	float GetSideX() { return m_side_x; }
	float GetSideY() { return m_side_y; }

private:
	float m_side_x, m_side_y;

};

#endif

