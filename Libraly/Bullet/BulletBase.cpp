#include "BulletBase.h"

BulletBase::BulletBase(float x_, float y_, float move_speed_, Direction direction_)
{
	//オブジェクトからの情報を格納
	m_pos.x = x_;
	m_pos.y = y_;
	m_speed = move_speed_;
	m_direction = direction_;

	//使用画像設定
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_draw_param.tex_size_x = M_BULLET_SYZE;
	m_draw_param.tex_size_y = M_BULLET_SYZE;

	//アニメーション用仮メンバ初期化
	m_anim_param.split_all		= 16;
	m_anim_param.split_width	= 4;
	m_anim_param.split_height	= 4;
	m_anim_param.change_flame	= 10;

	//移動距離判定用
	m_move_count		= 0.f;
	m_move_limit		= M_MOVE_LIMIT_DEFAULT;
}

BulletBase::~BulletBase()
{

}

void BulletBase::Init()
{
	//画像情報読み込み
	Load();
}

void BulletBase::Update()
{
	MoveUpdate();

	AnimationUpdate();
}

void BulletBase::Load()
{
	LoadTexture("Res/Tex/Effect/attack1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void BulletBase::MoveUpdate()
{
	//向きによって飛ぶ方向が変化
	if (m_direction == Direction::RIGHT) {
		m_pos.x += m_speed;
	}
	else if(m_direction==Direction::LEFT){
		m_pos.x -= m_speed;
	}
	
	//有効距離をカウント
	m_move_count += m_speed;

	if (m_move_count >= m_move_limit) {

		m_is_delete = true;

	}
	
}
