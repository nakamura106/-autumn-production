#ifndef ENEMYACHIEVE_H_
#define ENEMYACHIEVE_H_

#include "UiBase.h"
#include "../Object/Definition.h"

class EnemyAchieve :public UiBase
{
public:
	EnemyAchieve();
	~EnemyAchieve();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	const float ACHIEVE_POS_X = 1775.0f;
	const float ACHIEVE_POS_Y = 35.0f;

	AnimationParam m_anime_param;
	int m_animation_state;

};

#endif
