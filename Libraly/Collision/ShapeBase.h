#ifndef SHAPEBASE_H_
#define SHAPEBASE_H_

#include "../Object/Definition.h"


class ShapeBase
{
public:
	ShapeBase();
	virtual ~ShapeBase();

	virtual ShapeType GetShapeType()const = 0;

	float GetCenterX()const { return m_CenterX; }
	float GetCenterY()const { return m_CenterY; }

	float GetSideX()const { return m_side_x; }
	float GetSideY()const { return m_side_y; }

	float GetRadius()const { return m_radius; }

protected:
	ShapeType m_shape_type;

	// �I�u�W�F�N�g�̒��S���W
	float m_CenterX = 0.f, m_CenterY = 0.f;
	// ��`�̕ӂ̏c�Ɖ���
	float m_side_x = 0.f, m_side_y = 0.f;
	// �~�̔��a
	float m_radius = 0.f;

};


#endif


