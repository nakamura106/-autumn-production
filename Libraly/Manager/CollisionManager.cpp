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

			//�����蔻��
			if (IsHitTest(m_collision_obj_list[i], m_collision_obj_list[j])) {

				ObjectRavel j_obj = m_collision_obj_list[j]->GetRavel();
				ObjectRavel i_obj = m_collision_obj_list[i]->GetRavel();

				//���������I�I
				//�I�u�W�F�N�g�ɒʒm
				//�������œ��������I�u�W�F�N�g��n���A�������ł��̃I�u�W�F�N�g�������ɗ^������ʂ̒l��n��
				m_collision_obj_list[i]->HitAction(j_obj, m_collision_obj_list[j]->GetHitUseAtk(i_obj));
				m_collision_obj_list[j]->HitAction(i_obj, m_collision_obj_list[i]->GetHitUseAtk(j_obj));
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
	// AllHitTest();

	PlayerAndEnemyCol();
	PlayerAndMapObjCol();
	EnemyAndPBulletCol();
	PlayerAndEBulletCol();

	m_player_obj_list.clear();
	m_enemy_obj_list.clear();
	m_map_obj_list.clear();
	m_pBullet_obj_list.clear();
	m_eBullet_obj_list.clear();

}

void CollisionManager::ResetObject()
{
	//���vector�Ɠ��e�����ւ��邱�ƂŁA���g�����Z�b�g����
	std::vector<ObjectBase*>().swap(m_collision_obj_list);
	
}

bool CollisionManager::RunCollisionCalc(CollisionBase& collision, const std::list<ShapeBase*>& shapeGroup1, const std::list<ShapeBase*>& shapeGroup2)
{
	for (const auto& it1 : shapeGroup1) {
		for (const auto& it2 : shapeGroup2)
		{
			// �����蔻��̏���
			if (collision.CollisionCalc(*it1, *it2)) {
				return true;
			}
			
		}
	}

	return false;

}

void CollisionManager::PlayerAndEnemyCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_enemy_obj_list)
		{
			if (RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList()))
			{
				ObjectRavel j_obj = j->GetRavel();
				ObjectRavel i_obj = i->GetRavel();

  	 			i->HitAction(j_obj, j->GetHitUseAtk(i_obj));
				j->HitAction(i_obj, i->GetHitUseAtk(j_obj));
			}
		}
	}

}

void CollisionManager::PlayerAndEBulletCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_eBullet_obj_list)
		{
			if (RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList()))
			{
				ObjectRavel j_obj = j->GetRavel();
				ObjectRavel i_obj = i->GetRavel();

				i->HitAction(j_obj, j->GetHitUseAtk(i_obj));
				j->HitAction(i_obj, i->GetHitUseAtk(j_obj));
			}
		}
	}
}

void CollisionManager::PlayerAndMapObjCol()
{
	for (const auto& i : m_player_obj_list)
	{
		for (const auto& j : m_map_obj_list)
		{
			if (RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList()))
			{
				ObjectRavel j_obj = j->GetRavel();
				ObjectRavel i_obj = i->GetRavel();

				i->HitAction(j_obj, j->GetHitUseAtk(i_obj));
				j->HitAction(i_obj, i->GetHitUseAtk(j_obj));
			}
		}
	}
}

void CollisionManager::EnemyAndPBulletCol()
{
	for (const auto& i : m_pBullet_obj_list)
	{
		for (const auto& j : m_enemy_obj_list)
		{
			if (RunCollisionCalc(m_collision, i->GetShapeList(), j->GetShapeList()))
			{
				ObjectRavel j_obj = j->GetRavel();
				ObjectRavel i_obj = i->GetRavel();

				i->HitAction(j_obj, j->GetHitUseAtk(i_obj));
				j->HitAction(i_obj, i->GetHitUseAtk(j_obj));
			}
		}
	}
}



void CollisionManager::AddCollisionObject(ObjectBase* obj)
{
	//�I�u�W�F�N�g�𒆂ɓ����
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

void CollisionManager::AddMapColObject(ObjectBase* map_obj)
{
	m_map_obj_list.push_back(map_obj);
}
