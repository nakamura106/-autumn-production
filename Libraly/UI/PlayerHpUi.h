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

protected:
	// PlayerのHp状態を取得し続ける関数
	void GetPlayerHpState();

private:
	int m_hp_state;	// PlayerHPの状態を列挙型で保存する

};

#endif

