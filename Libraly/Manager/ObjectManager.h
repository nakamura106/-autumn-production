#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"
#include "../Utility/HitTest.h"

class ObjectManager
{
public:
	static ObjectManager* Instance();
	
	// マネージャー初期化、コンストラクタ時のみ
	void Init();
	// オブジェクト作成
	void CreateObject();
	void Update();
	void Draw();

	ObjectBase* GetPlayerObject()
	{
		if (chara_objects[2] != nullptr)
		{
			return chara_objects[2];
		}
	}

	ObjectBase* GetCharaObject(ObjectRavel ravel);

protected:
	ObjectManager();
	~ObjectManager();

private:

	static ObjectManager* p_instance;	
	static const int MAX_CHARA_OBJ = 7;
	ObjectBase* chara_objects[MAX_CHARA_OBJ];

};


#endif
