#pragma once

#include"../PlayerBase.h"

class TubaPlayer:public PlayerBase
{
public:
	TubaPlayer();
	~TubaPlayer();

	void Init()override;

	void SetRectangle();

	void Jump();

	void Load()override;
private:

};
