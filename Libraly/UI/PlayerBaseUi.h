#ifndef PLAYERBASEUI_H_
#define PLAYERBASEUI_H_

#include "UiBase.h"

class PlayerBaseUi :public UiBase
{
public:
	PlayerBaseUi();
	~PlayerBaseUi();

	void Init()override;
	void Update()override;
	void Draw()override;


private:
	int m_bullet_type;

	void ReleaseBulletType();

};

#endif
