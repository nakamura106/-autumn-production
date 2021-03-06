#include "AnyCollision.h"
#include "CircleAndCircle.h"
#include "CircleAndRect.h"
#include "RectAndRect.h"

AnyCollision::AnyCollision()
{

	for (int i = 0; i < static_cast<unsigned int>(ShapeType::ShapeTypeMax); ++i)
	{
		for (int j = 0; j < static_cast<unsigned int>(ShapeType::ShapeTypeMax); ++j)
		{
			m_collision_table[i][j] = nullptr;
		}
	}

	m_collision_table[static_cast<unsigned int>(ShapeType::Shape_Circle)][static_cast<unsigned int>(ShapeType::Shape_Circle)] = new CircleAndCircle;
	m_collision_table[static_cast<unsigned int>(ShapeType::Shape_Circle)][static_cast<unsigned int>(ShapeType::Shape_Rect)] = new CircleAndRect;
	m_collision_table[static_cast<unsigned int>(ShapeType::Shape_Rect)][static_cast<unsigned int>(ShapeType::Shape_Circle)] = new CircleAndRect;
	m_collision_table[static_cast<unsigned int>(ShapeType::Shape_Rect)][static_cast<unsigned int>(ShapeType::Shape_Rect)] = new RectAndRect;

}

AnyCollision::~AnyCollision()
{
	for (int i = 0; i < static_cast<unsigned int>(ShapeType::ShapeTypeMax); ++i)
	{
		for (int j = 0; j < static_cast<unsigned int>(ShapeType::ShapeTypeMax); ++j)
		{
			if (m_collision_table[i][j] != nullptr)
			{
				delete m_collision_table[i][j];
			}
		}
	}
}

bool AnyCollision::CollisionCalc(const ShapeBase& shape1, const ShapeBase& shape2)
{
	return m_collision_table[static_cast<unsigned int>(shape1.GetShapeType())][static_cast<unsigned int>(shape2.GetShapeType())]->CollisionCalc(shape1, shape2);
}

