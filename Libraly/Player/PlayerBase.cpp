#include"PlayerBase.h"

PlayerBase::PlayerBase()
{

}
PlayerBase::~PlayerBase()
{
	//bullet‰ğ•ú
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
		//’e‚ÌXV
		bullet_list[i]->Update();

		//’e‚Ìis_delete‚ªtrue‚Ìê‡A’eÁ–Å
		if (bullet_list[i]->GetIsDelete()) {
			//ƒƒ‚ƒŠ‰ğ•ú
			delete bullet_list[i];

			//’e‚ğÁ–Å
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}