#ifndef SHAPELINE_H_
#define SHAPELINE_H_

#include "../ShapeBase.h"

class ShapeLine :public ShapeBase
{
public:
	ShapeLine();
	~ShapeLine()override;

	ShapeType GetShapeType()const override { return m_shape_type; }


private:


};

#endif

