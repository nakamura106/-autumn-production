#pragma once

#include"../Object/ObjectBase.h"

class Map:public ObjectBase
{
public:
	Map();
	~Map();
	void Init();
	void Create();
	void Load();
	void Update();
	void Draw();



};
