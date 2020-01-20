#ifndef SHAPEBASE_H_
#define SHAPEBASE_H_

#include "../Object/Definition.h"


class ShapeBase
{
public:
	ShapeBase();
	virtual ~ShapeBase();

	virtual ShapeType GetShapeType()const = 0;

	float GetCenterX() { return m_CenterX; }
	float GetCenterY() { return m_CenterY; }

protected:
	ShapeType m_shape_type;

	float m_CenterX, m_CenterY;

};


#endif


