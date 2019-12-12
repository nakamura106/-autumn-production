#include "EndSceneObject.h"
#include "../../Engine/Graphics.h"
#include "../../Texture/Texture.h"
#include "../../DataBank/DataBank.h"


EndSceneObject::EndSceneObject()
{
	for (int i = 0; i < 3; i++)
	{
		m_draw_pos[i].x = 0.0f;
		m_draw_pos[i].y = 0.0f;
		m_param[i].category_id = TEXTURE_CATEGORY_GAMEEND;
	}

	is_clear = false;
}

EndSceneObject::~EndSceneObject()
{
}

void EndSceneObject::Init()
{
	LoadTexture("Res/Tex/EndScene/GameClear.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameClearBgTex);
	LoadTexture("Res/Tex/EndScene/GameOver.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameOverBgTex);
	LoadTexture("Res/Tex/EndScene/GameOverR.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameOverRTex);
	LoadTexture("Res/Tex/EndScene/Back.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameBuckTex);
	
	is_clear = DataBank::Instance()->GetIsGameClear();

	if (is_clear == true)
	{
		m_param[0].texture_id = GameEndCategoryTextureList::GameClearBgTex;
	}
	else {
		m_param[0].texture_id = GameEndCategoryTextureList::GameOverBgTex;
	}
	m_draw_pos[0].x = 0.0f;
	m_draw_pos[0].y = 0.0f;
	m_draw_pos[1].x = 230.0f;
	m_draw_pos[1].y = 180.0f;
	m_param[1].texture_id = GameEndCategoryTextureList::GameOverRTex;
	m_draw_pos[2].x = 700.0f;
	m_draw_pos[2].y = 880.0f;
	m_param[2].texture_id = GameEndCategoryTextureList::GameBuckTex;
}

void EndSceneObject::Update()
{

}

void EndSceneObject::Draw()
{
	if (is_clear == false)
	{
		DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
	}
	else {
		DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
		DrawTexture(m_draw_pos[1].x, m_draw_pos[1].y, GetTexture(m_param[1].category_id, m_param[1].texture_id));
		DrawTexture(m_draw_pos[2].x, m_draw_pos[2].y, GetTexture(m_param[2].category_id, m_param[2].texture_id));
	}
	
}
