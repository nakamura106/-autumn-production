#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"
#include "../Utility/HitTest.h"

class ObjectManager
{
public:
	static ObjectManager* Instance();
	
	// �}�l�[�W���[�������A�R���X�g���N�^���̂�
	void Init();
	// �I�u�W�F�N�g�쐬
	void CreateObject();
	void Update();
	void Draw();

	ObjectBase* GetPlayerObject()
	{
		for (int i = 0; i < MAX_CHARA_OBJ; ++i) {
			if (chara_objects[i] == nullptr)continue;

		}
		return chara_objects[1];
	}

protected:
	ObjectManager();
	~ObjectManager();

private:

	static ObjectManager* p_instance;	
	static const int MAX_CHARA_OBJ = 5;
	ObjectBase* chara_objects[MAX_CHARA_OBJ];

};


#endif
