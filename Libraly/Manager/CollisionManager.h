#pragma once

#include"../Object/ObjectBase.h"
#include<vector>

#include "../Collision/CollisionCalc/CollisionBase.h"
#include "../Collision/CollisionCalc/AnyCollision.h"
#include <list>

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

	// �e�I�u�W�F�N�g��z��ɒǉ�����
	void AddPlayerColObject(ObjectBase* p_obj);
	void AddEnemyColObject(ObjectBase* e_obj);
	void AddPBulletColObject(ObjectBase* p_b_obj);
	void AddEBulletColObject(ObjectBase* e_b_obj);

private:
	CollisionManager();
	~CollisionManager();

	/*�����蔻��֐�*/
	void AllHitTest();

	/*�I�u�W�F�N�g���X�g�̃��Z�b�g(��ɂ���)*/
	void ResetObject();

	std::vector<ObjectBase*> m_collision_obj_list;//�����蔻����s���I�u�W�F�N�g�̃��X�g

	std::vector<ObjectBase*> m_player_obj_list;
	std::vector<ObjectBase*> m_enemy_obj_list;
	std::vector<ObjectBase*> m_map_obj_list;
	std::vector<ObjectBase*> m_pBullet_obj_list;
	std::vector<ObjectBase*> m_eBullet_obj_list;

	// �V���������蔻��֐�
	bool RunCollisionCalc(CollisionBase& collision, const std::list<ShapeBase*>& shapeGroup1, const std::list<ShapeBase*>& shapeGroup2);

	void PlayerAndEnemyCol();
	void PlayerAndEBulletCol();
	void PlayerAndMapObjCol();
	void EnemyAndPBulletCol();

	AnyCollision m_collision;
	
};
