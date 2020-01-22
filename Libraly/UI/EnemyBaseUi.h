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
	void Draw()override;
	
private:

};

#endif

