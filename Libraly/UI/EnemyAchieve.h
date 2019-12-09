#ifndef ENEMYACHIEVE_H_
#define ENEMYACHIEVE_H_

#include "UiBase.h"

class EnemyAchieve :public UiBase
{
public:
	EnemyAchieve();
	~EnemyAchieve();

	void Init()override;
	void Update()override;
	void Draw()override;

private:


};

#endif
