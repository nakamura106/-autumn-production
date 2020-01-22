#ifndef SHAPEBASE_H_
#define SHAPEBASE_H_

#include "../Object/Definition.h"


class ShapeBase
{
public:
	ShapeBase();
	virtual ~ShapeBase();

	void Update(float x, float y, int direction);

	virtual ShapeType GetShapeType()const = 0;

	float GetCenterX()const { return m_CenterX; }
	float GetCenterY()const { return m_CenterY; }

	float GetSideX()const { return m_side_x; }
	float GetSideY()const { return m_side_y; }

	float GetRadius()const { return m_radius; }

	int GetDirection()const { return m_direction; }

protected:
	ShapeType m_shape_type;

	// オブジェクトの中心座標
	float m_CenterX, m_CenterY;
	// 矩形の辺の縦と横幅
	float m_side_x, m_side_y;
	// 円の半径
	float m_radius;
	// GetPosからのオフセット値
	float m_offset_x, m_offset_y;
	// オブジェクトの左右情報
	int m_direction;
	// 画像サイズ X
	float m_tex_x;

};


#endif


