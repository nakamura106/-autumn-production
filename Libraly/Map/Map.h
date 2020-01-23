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
	
	//!< 更新関数(毎フレーム更新が必要なもの等)
	void Update()override;
	//!< 描画用関数(背景やオブジェクトを描画する)
	virtual void Draw()override;
	//!< 未使用
	void Create(){}



	

private:

	//!< マップスクロール関数(プレイヤーの動きに合わせてスクロール速度が違う)
	void MapScroll(int direction_);

	void WaveChange(float enemyX_);

	//!< 当たり判定関数(プレイヤーがオブジェクトに当たっているか判定する関数)
	void HitJudgement();

protected:
	float floor1;
	float floor2;
	float obj[10];



	



};

class Fg :public Map
{
public:
	//!< 初期化関数(座標など)
	void Init()override;
	//!< 画像読込関数関数
	virtual void Load();
	//!< 更新関数(毎フレーム更新が必要なもの等)
	void Update()override;
	//!< 描画用関数(背景やオブジェクトを描画する)
	virtual void Draw()override;
	//!< 未使用
	void Create() {}

	

private:
	void MapScroll(int direction_);
	void WaveChange(float enemyX_);
protected:
	float fg;
};

