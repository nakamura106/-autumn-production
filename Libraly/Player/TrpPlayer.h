#pragma once

#pragma once

#include"PlayerBase.h"


class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();

	 void Init()override;
	 void Load()override;
	 void Create()override;
	 void Update()override;
	 void Draw()override;
	 void P_Controll()override;
	 void InitAnimation()override;
	 void DrawAnimation()override;
	
	 void Jump();
	 void GetMotion(int Llist,int Rlist);
	 Position GetPos()override;

private:
	
};

