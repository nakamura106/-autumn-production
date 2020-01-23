#ifndef LIFECUTUI_H_
#define LIFECUTUI_H_

#include "../UI/UiBase.h"

class LifeCutUi :public UiBase
{
public:
	LifeCutUi();
	~LifeCutUi();

	void Init()override;
	void Update()override;

private:

	const float LIFE_CUT_POSX = 1535.0f;
	const float LIFE_CUT_POSY = 75.0f;

};

#endif

