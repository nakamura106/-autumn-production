#ifndef SHAPERECT_H_
#define SHAPERECT_H_

#include "../ShapeBase.h"

class ShapeRect :public ShapeBase
{
public:
	ShapeRect();
	~ShapeRect();

	ShapeType GetShapetype() { return m_shape_type; }

private:


};

#endif

