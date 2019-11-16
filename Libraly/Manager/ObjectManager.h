#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void CreateObject();
	void Update();
	void Draw();


private:
	ObjectBase* chara_objects[50];
	ObjectBase* bullets_objects[100];

};



#endif
