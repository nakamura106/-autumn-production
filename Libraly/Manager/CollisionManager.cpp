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

	for (int i = 0;i < static_cast<int>(m_collision_obj_list.size());++i) {

		for (int j = 0;j < static_cast<int>(m_collision_obj_list.size());++j) {

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
	AllHitTest();

	PlayerAndEnemyCol();
	PlayerAndEBulletCol();
	PlayerAndMapObjCol();
	EnemyAndPBulletCol();

}

void CollisionManager::ResetObject()
{
	//空のvectorと内容を入れ替えることで、中身をリセットする
	std::vector<ObjectBase*>().swap(m_collision_obj_list);
	
}

bool CollisionManager::RunCollisionCalc(CollisionBase& collision, const std::list<ShapeBase*>& shapeGroup1, const std::list<ShapeBase*>& shapeGroup2)
{
	for (const auto& it1 : shapeGroup1) {
		for (const auto& it2 : shapeGroup2)
		{
			// 当たり判定の処理
			if (collision.CollisionCalc(*it1, *it2)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void CollisionManager::PlayerAndEnemyCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_enemy_obj_list)
		{
			RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList());
		}
	}

}

void CollisionManager::PlayerAndEBulletCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_eBullet_obj_list)
		{
			RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList());
		}
	}
}

void CollisionManager::PlayerAndMapObjCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_map_obj_list)
		{
			RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList());
		}
	}
}

void CollisionManager::EnemyAndPBulletCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_enemy_obj_list)
		{
			RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList());
		}
	}
}



void CollisionManager::AddCollisionObject(ObjectBase* obj)
{
	//オブジェクトを中に入れる
	m_collision_obj_list.push_back(obj);
}

void CollisionManager::AddPlayerColObject(ObjectBase* p_obj)
{
	m_player_obj_list.push_back(p_obj);
}

void CollisionManager::AddEnemyColObject(ObjectBase* e_obj)
{
	m_enemy_obj_list.push_back(e_obj);
}

void CollisionManager::AddPBulletColObject(ObjectBase* p_b_obj)
{
	m_pBullet_obj_list.push_back(p_b_obj);
}

void CollisionManager::AddEBulletColObject(ObjectBase* e_b_obj)
{
	m_eBullet_obj_list.push_back(e_b_obj);
}
