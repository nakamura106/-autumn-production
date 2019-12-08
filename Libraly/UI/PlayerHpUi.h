#ifndef PLAYERHPUI_H_
#define PLAYERHPUI_H_

#include "UiBase.h"

class PlayerHpUi :public UiBase
{
public:
	PlayerHpUi();
	~PlayerHpUi();

	void Init();
	void Update();
	void Draw();

protected:
	// Player‚ÌHpó‘Ô‚ğæ“¾‚µ‘±‚¯‚éŠÖ”
	void GetPlayerHpState();

private:
	int m_hp_state;	// PlayerHP‚Ìó‘Ô‚ğ—ñ‹“Œ^‚Å•Û‘¶‚·‚é

};

#endif

