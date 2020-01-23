#include"MapObjectBase.h"
#include"../../Manager/ObjectManager.h"
#include"../../Engine/Input.h"
#include"../../Object/Definition.h"
#include"../../DataBank/DataBank.h"
#include "../../Manager/CollisionManager.h"


MapObjectBase::MapObjectBase()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 0;
	m_pos.y = 0;
	m_direction = Direction::RIGHT;
}

void MapObjectBase::Update()
{
	if ((IsButtonPush(LeftButton) ||GetKey(LEFT_KEY) == true) )
	{
		MoveUpdate(LEFT);
	}
	if ((IsButtonPush(RightButton) || GetKey(RIGHT_KEY) == true) )
	{
		MoveUpdate(RIGHT);
	}

	CollisionParamUpdate();
}

void MapObjectBase::MoveUpdate(Direction direction_)
{
	//�������E�������}�b�v�̒[��-3800�ȏ�̎��ɉE�ɃX�N���[������
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen && DataBank::Instance()->GetfgPos() >= -3550.0f && direction_ == RIGHT)
	{
		m_pos.x -= P_speed;
	}
	//���������������}�b�v�̒[��0�ȉ��̎��ɍ��ɃX�N���[������
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen && DataBank::Instance()->GetfgPos() < 0.0f && direction_ == LEFT)
	{
		m_pos.x += P_speed;
	}
}

void MapObjectBase::CollisionParamUpdate()
{
	for (const auto& i : m_shape_list)
	{
		i->Update(m_pos.x, m_pos.y, m_direction);
	}

	CollisionManager::GetInstance().AddMapColObject(this);
}
