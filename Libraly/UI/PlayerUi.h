#ifndef PLAYERUI_H_
#define PLAYERUI_H_

#include "UiBase.h"

class PlayerUi :public UiBase
{
public:
	PlayerUi();
	~PlayerUi();

	void Init()override;
	void Update()override;

private:

};

#endif
