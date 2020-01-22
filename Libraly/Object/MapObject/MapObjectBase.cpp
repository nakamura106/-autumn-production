#include"MapObjectBase.h"
#include"../../Manager/ObjectManager.h"
#include"../../Engine/Input.h"
#include"../../Object/Definition.h"
#include"../../DataBank/DataBank.h"


MapObjectBase::MapObjectBase()
{
	m_obj_ravel = ObjectRavel::Ravel_MapObj;
	m_pos.x = 0;
	m_pos.y = 0;
}

void MapObjectBase::Update()
{
	if (GetKey(LEFT_KEY) == true )
	{
		MoveUpdate(LEFT);
	}
	if (GetKey(RIGHT_KEY) == true )
	{
		MoveUpdate(RIGHT);
	}
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