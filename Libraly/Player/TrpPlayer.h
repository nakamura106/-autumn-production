#pragma once


#include"PlayerBase.h"



class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	 //!< 初期化関数
	 void Init()override;
	
	 void SetRectangle()override;

private:
	


	//!< 画像読込用関数(ゲームシーンにべた書き予定)
	void Load()override;


	



	

	int timer;				//音符生成用

	int timer2;				//Releasenote()用

	bool m_do_bullet_firing;

	bool m_is_release;

	bool m_do_attack;

	 int notebox[3];
};

