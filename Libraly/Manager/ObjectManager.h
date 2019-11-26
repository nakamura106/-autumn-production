#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	// マネージャー初期化、コンストラクタ時のみ
	void Init();
	// オブジェクト作成
	void CreateObject();
	void Update();
	void Draw();


private:
	static const int MAX_CHARA_OBJ = 50;

	ObjectBase* chara_objects[MAX_CHARA_OBJ];

};



#endif
