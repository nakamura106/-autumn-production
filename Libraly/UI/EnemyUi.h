#ifndef ENEMYUI_H_
#define ENEMYUI_H_

#include "UiBase.h"

class EnemyUi :public UiBase
{
public:
	EnemyUi();
	~EnemyUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif

