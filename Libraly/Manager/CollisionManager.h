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

	/*当たり判定を行うオブジェクトの追加*/
	void AddCollisionObject(ObjectBase* obj);

private:
	CollisionManager();
	~CollisionManager();

	/*当たり判定関数*/
	void AllHitTest();

	/*オブジェクトリストのリセット(空にする)*/
	void ResetObject();

	std::vector<ObjectBase*> m_collision_obj_list;//当たり判定を行うオブジェクトのリスト


};
