#ifndef PLAYERBRASSUI_H_
#define PLAYERBRASSUI_H_

#include "UiBase.h"

class PlayerBrassUi :public UiBase
{
public:
	PlayerBrassUi();
	~PlayerBrassUi();

	void Init()override;
	void Update()override;

private:
	const float BRASSUI_POS_X = 100.0f;
	const float BRASSUI_POS_Y = 70.0f;

};

#endif

