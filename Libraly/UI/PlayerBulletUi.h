#ifndef PLAYERBULLETUI_H_
#define PLAYERBULLETUI_H_

#include "UiBase.h"

class PlayerBulletUi :public UiBase
{
public:
	PlayerBulletUi();
	~PlayerBulletUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif

