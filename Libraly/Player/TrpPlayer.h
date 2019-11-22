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
	void P_Controll();
	Position GetPos();

private:
	
};

