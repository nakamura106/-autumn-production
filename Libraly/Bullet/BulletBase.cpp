#include "BulletBase.h"

BulletBase::BulletBase()
{
	Init();

	Load();
}

BulletBase::~BulletBase()
{

}

void BulletBase::Init()
{
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;

	/*アニメーション用仮メンバ初期化*/
	m_anim_timer		= 0;
	m_anim_tex_all		= 16;
	m_anim_tex_width	= 4;
	m_anim_tex_height	= 4;
	m_anim_flame		= 5;

	m_move_count	= 0.f;
	m_move_limit	= 500.f;
	m_speed			= 5.f;

	//座標仮指定
	m_pos.y = 500.f;
	m_pos.x = 0.f;
}

void BulletBase::Update()
{
	AnimationUpdate();
}

void BulletBase::Draw()
{
	//消滅状態の場合、描画しない(デバッグ用)
	if (m_is_delete) return;

	DrawUVTexture(
		m_pos.x,
		m_pos.y,
		M_BULLET_SYZE,
		M_BULLET_SYZE,
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
		m_draw_param.tu / m_anim_tex_width,
		m_draw_param.tv / m_anim_tex_height
	);
}

void BulletBase::Load()
{
	LoadTexture("Res/Tex/Effect/attack1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void BulletBase::AnimationUpdate() 
{

	++m_anim_timer;

	if (m_anim_timer >= m_anim_flame) {//画像を変更する

		m_anim_timer = 0;

		//横分割枚目を加算
		++m_draw_param.tu;

		//横分割枚目が画像の分割数以上の場合
		if (m_draw_param.tu > m_anim_tex_width) {

			m_draw_param.tu = 1;

			//縦分割枚目を加算
			++m_draw_param.tv;

			//縦分割枚目が画像の分割数以上の場合
			if (m_draw_param.tv > m_anim_tex_height) {

				m_draw_param.tv = 1;

			}
		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (((m_draw_param.tv - 1) * m_anim_tex_width + m_draw_param.tu) > m_anim_tex_all) {

			m_draw_param.tu = m_draw_param.tv = 1;

		}

	}

}

void BulletBase::MoveUpdate()
{
	m_pos.x += m_speed;

	m_move_count += m_speed;

	if (m_move_count >= m_move_limit) {

		m_is_delete = true;

	}
	
}
