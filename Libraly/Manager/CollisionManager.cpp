#include"CollisionManager.h"
#include"../Player/TrpPlayer.h"
#include"../Enemy/Mouse.h"
#include"../Utility/HitTest.h"

CollisionManager::CollisionManager()
{
	Init();
}

CollisionManager::~CollisionManager()
{
	
}

void CollisionManager::AllHitTest()
{

	for (int i = 0;i < m_collision_obj_list.size();++i) {

		for (int j = 0;j < m_collision_obj_list.size();++j) {

			if (i == j)continue;

			//�����蔻��
			if (IsHitTest(m_collision_obj_list[i], m_collision_obj_list[j])) {
				//���������I�I
				//�I�u�W�F�N�g�ɒʒm
				m_collision_obj_list[i]->HitAction(m_collision_obj_list[j]->GetRavel(), m_collision_obj_list[j]->GetHitUseAtk());
				m_collision_obj_list[j]->HitAction(m_collision_obj_list[i]->GetRavel(), m_collision_obj_list[i]->GetHitUseAtk());
			}

		}
	}

	ResetObject();
}

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{

}

void CollisionManager::ResetObject()
{
	//���vector�Ɠ��e�����ւ��邱�ƂŁA���g�����Z�b�g����
	std::vector<ObjectBase*>().swap(m_collision_obj_list);
	
}

void CollisionManager::AddCollisionObject(ObjectBase* obj)
{
	//�I�u�W�F�N�g�𒆂ɓ����
	m_collision_obj_list.push_back(obj);
}
