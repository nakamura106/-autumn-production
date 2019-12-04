#pragma once

#include"../Object/ObjectBase.h"
#include"../Object/Definition.h"

class Map:public ObjectBase
{
public:
	Map();
	~Map();
	//!< 初期化関数(座標など)
	void Init()override;
	//!< 画像読込関数関数
	void Load()override;
	//!< 更新関数(毎フレーム更新が必要なもの等)
	void Update()override;
	//!< 描画用関数(背景やオブジェクトを描画する)
	void Draw()override;
	//!< 未使用
	void Create(){}

private:

	//!< マップスクロール関数(プレイヤーの動きに合わせてスクロール速度が違う)
	void MapScroll(int direction_);
	//!< 当たり判定関数(プレイヤーがオブジェクトに当たっているか判定する関数)
	void HitJudgement();

	Position m_pos;			// 座標
	DrawParam m_draw_param;	// 描画用構造体
	float m_speed;			// マップのスクロール速度




};
