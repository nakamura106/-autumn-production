#pragma once

#include"../Object/ObjectBase.h"
#include<vector>

class CollisionManager
{
public:
	static CollisionManager& GetInstance() {
		static CollisionManager c_manager;
		return c_manager;
	}
	void Init();
	void Update();

	/*�����蔻����s���I�u�W�F�N�g�̒ǉ�*/
	void AddCollisionObject(ObjectBase* obj);

private:
	CollisionManager();
	~CollisionManager();

	/*�����蔻��֐�*/
	void AllHitTest();

	/*�I�u�W�F�N�g���X�g�̃��Z�b�g(��ɂ���)*/
	void ResetObject();

	std::vector<ObjectBase*> m_collision_obj_list;//�����蔻����s���I�u�W�F�N�g�̃��X�g


};
