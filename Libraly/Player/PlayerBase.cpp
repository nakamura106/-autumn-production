#include"PlayerBase.h"

PlayerBase::PlayerBase()
{

}
PlayerBase::~PlayerBase()
{
	//bullet���
	for (auto& i : bullet_list) {
		delete i;
		i = nullptr;
	}
	std::vector<PlayerBullet*>().swap(bullet_list);
}
void PlayerBase::Create()
{

}
void PlayerBase::BulletControl()
{
	for (int i = 0; i < static_cast<int>(bullet_list.size()); ++i) {
		//�e�̍X�V
		bullet_list[i]->Update();

		//�e��is_delete��true�̏ꍇ�A�e����
		if (bullet_list[i]->GetIsDelete()) {
			//���������
			delete bullet_list[i];

			//�e������
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}