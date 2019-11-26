#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Object/ObjectBase.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	// �}�l�[�W���[�������A�R���X�g���N�^���̂�
	void Init();
	// �I�u�W�F�N�g�쐬
	void CreateObject();
	void Update();
	void Draw();


private:
	static const int MAX_CHARA_OBJ = 50;

	ObjectBase* chara_objects[MAX_CHARA_OBJ];

};



#endif
