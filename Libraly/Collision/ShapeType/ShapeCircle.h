#ifndef SHAPECIRCLE_H_
#define SHAPECIRCLE_H_

#include "../ShapeBase.h"

class ShapeCircle :public ShapeBase
{
public:
	ShapeCircle();
	~ShapeCircle();

	ShapeType GetShapeType() { return m_shape_type; }

private:

};

#endif

