#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void CreateObject();
	void Update();
	void Draw();


private:
	static const int MAX_CHARA_OBJ = 50;
	static const int MAX_BULLET_OBJ = 100;

	ObjectBase* chara_objects[50];
	ObjectBase* bullets_objects[MAX_BULLET_OBJ];

};



#endif
