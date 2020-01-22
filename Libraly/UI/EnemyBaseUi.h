#ifndef ENEMYBASEUI_H_
#define ENEMYBASEUI_H_

#include "UiBase.h"

class EnemyBaseUi :public UiBase
{
public:
	EnemyBaseUi();
	~EnemyBaseUi();

	void Init()override;
	void Update()override;
	
private:
	const float ENEMYBASE_UI_POS_X = 1050.0f;
	const float ENEMYBASE_UI_POS_Y = 30.0f;

};

#endif

