#ifndef SHAPEBASE_H_
#define SHAPEBASE_H_

#include "../Object/Definition.h"

class ShapeBase
{
public:
	ShapeBase();
	virtual ~ShapeBase();

	virtual ShapeType GetShapeType()const = 0;

protected:
	ShapeType m_shape_type;


};


#endif


