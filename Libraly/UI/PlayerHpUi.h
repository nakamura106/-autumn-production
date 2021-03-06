#ifndef PLAYERHPUI_H_
#define PLAYERHPUI_H_

#include "UiBase.h"

class PlayerHpUi :public UiBase
{
public:
	PlayerHpUi();
	~PlayerHpUi();

	void Init()override;
	void Update()override;
	void Draw()override;

protected:
	// PlayerのHp状態を取得し続ける関数
	void GetPlayerHpState();

private:
	int m_hp_state;	// PlayerHPの状態を列挙型で保存する

	const float PLAYERHP_UI_POS_X = 20.0f;
	const float PLAYERHP_UI_POS_Y = 20.0f;

};

#endif

