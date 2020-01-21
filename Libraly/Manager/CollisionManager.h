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

	/*当たり判定を行うオブジェクトの追加*/
	void AddCollisionObject(ObjectBase* obj);

	// 各オブジェクトを配列に追加する
	void AddPlayerColObject(ObjectBase* p_obj);
	void AddEnemyColObject(ObjectBase* e_obj);
	void AddPBulletColObject(ObjectBase* p_b_obj);
	void AddEBulletColObject(ObjectBase* e_b_obj);

private:
	CollisionManager();
	~CollisionManager();

	/*当たり判定関数*/
	void AllHitTest();

	/*オブジェクトリストのリセット(空にする)*/
	void ResetObject();

	std::vector<ObjectBase*> m_collision_obj_list;//当たり判定を行うオブジェクトのリスト

	std::vector<ObjectBase*> m_player_obj_list;
	std::vector<ObjectBase*> m_enemy_obj_list;
	std::vector<ObjectBase*> m_map_obj_list;
	std::vector<ObjectBase*> m_pBullet_obj_list;
	std::vector<ObjectBase*> m_eBullet_obj_list;

	// 新しい当たり判定関数
	bool RunCollisionCalc(CollisionBase& collision, const std::list<ShapeBase*>& shapeGroup1, const std::list<ShapeBase*>& shapeGroup2);

	void PlayerAndEnemyCol();
	void PlayerAndEBulletCol();
	void PlayerAndMapObjCol();
	void EnemyAndPBulletCol();

	AnyCollision m_collision;
	
};
