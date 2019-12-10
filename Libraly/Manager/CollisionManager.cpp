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

			//当たり判定
			if (IsHitTest(m_collision_obj_list[i], m_collision_obj_list[j])) {
				//当たった！！
				//オブジェクトに通知
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
	//空のvectorと内容を入れ替えることで、中身をリセットする
	std::vector<ObjectBase*>().swap(m_collision_obj_list);
	
}

void CollisionManager::AddCollisionObject(ObjectBase* obj)
{
	//オブジェクトを中に入れる
	m_collision_obj_list.push_back(obj);
}
