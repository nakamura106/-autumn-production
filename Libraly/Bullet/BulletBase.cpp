#include "BulletBase.h"


BulletBase::BulletBase(float x_, float y_, float move_speed_, Direction direction_)
{
	//オブジェクトからの情報を格納
	m_pos.x = x_;
	m_map_pos = x_;
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

	//当たり判定用
	m_rect_param.shift_x = M_BULLET_SYZE / 2.f;
	m_rect_param.shift_y = M_BULLET_SYZE / 2.f;
	m_rect_param.width = M_BULLET_SYZE;
	m_rect_param.height = M_BULLET_SYZE;

	//移動距離判定用
	m_move_count		= 0.f;
	m_move_limit		= M_MOVE_LIMIT_DEFAULT;

	CalcDrawPosition();
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
	ObjectBase::Update();

	MoveUpdate();

	AnimationUpdate();

	CalcDrawPosition();
}

void BulletBase::Load()
{
}



void BulletBase::MoveUpdate()
{
	
	//向きによって飛ぶ方向が変化
	if (m_direction == Direction::RIGHT) {
		m_map_pos += m_speed;
	}
	else if(m_direction==Direction::LEFT){
		m_map_pos -= m_speed;
	}
	
	//有効距離をカウント
	m_move_count += m_speed;

	if (m_move_count >= m_move_limit) {

		m_is_delete = true;

	}
	
}
