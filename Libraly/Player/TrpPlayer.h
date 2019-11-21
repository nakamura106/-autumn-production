#pragma once

#pragma once

#include"PlayerBase.h"

class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();

	void Init();
	void Load();
	void Create();
	void Update();
	void Draw();
	Position GetPos();

private:
	
};

