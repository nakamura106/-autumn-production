#pragma once


#include"PlayerBase.h"



class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	 //!< �������֐�
	 void Init()override;
	
	 void SetRectangle()override;

	
private:
	


};

