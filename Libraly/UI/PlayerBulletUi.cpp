#include "PlayerBulletUi.h"
#include"../DataBank/DataBank.h"

PlayerBulletUi::PlayerBulletUi()
{
	Init();
}

PlayerBulletUi::~PlayerBulletUi()
{

}

void PlayerBulletUi::Init()
{
	

	m_pos.x = PLAYERBULLET_UI_POS_X;
	m_pos.y = PLAYERBULLET_UI_POS_Y;

	m_param.texture_id = GameCategoryTextureList::GameBulletUi_BlueLeft;
	m_draw_texid1 = GameCategoryTextureList::GameBulletUi_BlueLeft;
	m_draw_texid2 = GameCategoryTextureList::GameBulletUi_BlueCenter;
	m_draw_texid3 = GameCategoryTextureList::GameBulletUi_BlueRight;

}

void PlayerBulletUi::Update()
{
	m_notes_box[0] = DataBank::Instance()->GetNote1();
	m_notes_box[1] = DataBank::Instance()->GetNote2();
	m_notes_box[2] = DataBank::Instance()->GetNote3();

	if (m_notes_box[0] == A){
		m_draw_texid1 = GameCategoryTextureList::GameBulletUi_BlueLeft;
		if (m_notes_box[1] == A){
			m_draw_texid2 = GameCategoryTextureList::GameBulletUi_BlueCenter;
				if (m_notes_box[2] == A){
					m_draw_texid3 = GameCategoryTextureList::GameBulletUi_BlueRight;
				}
		}
		else if(m_notes_box[1] == B) {
			m_draw_texid2 = GameCategoryTextureList::GameBulletUi_GreenCenter;
			if (m_notes_box[2] == A){
				m_draw_texid3 = GameCategoryTextureList::GameBulletUi_YellowRight;
			}
		}
	}
	else if (m_notes_box[0] == B){
		m_draw_texid1 = GameCategoryTextureList::GameBulletUi_RedLeft;
		if (m_notes_box[1] == A){
			m_draw_texid2 = GameCategoryTextureList::GameBulletUi_PinkCenter;
			if (m_notes_box[2] == B){
				m_draw_texid3 = GameCategoryTextureList::GameBulletUi_PurpleRight;
			}
		}
		else if (m_notes_box[1] == B){
			m_draw_texid2 = GameCategoryTextureList::GameBulletUi_RedCenter;
			if (m_notes_box[2] == B){
				m_draw_texid3 = GameCategoryTextureList::GameBulletUi_RedRight;
			}
		}
	}


}

void PlayerBulletUi::Draw()
{
	if (m_notes_box[0] != 0)
	{
		DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_draw_texid1));
	}
	if (m_notes_box[1] != 0)
	{
		DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_draw_texid2));
	}
	if (m_notes_box[2] != 0)
	{
		DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_draw_texid3));
	}
	
}

