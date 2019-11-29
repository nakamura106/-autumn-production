#pragma once

#include"../Object/ObjectBase.h"
#include"../Object/Definition.h"

class Map
{
public:
	Map();
	~Map();
	void Init();
	void Load();
	void Update();
	void MapScroll();
	void Draw();

private:
	Position m_pos;			//座標
	DrawParam m_draw_param;	// 描画用構造体
	float m_speed;			//マップのスクロール速度



};
