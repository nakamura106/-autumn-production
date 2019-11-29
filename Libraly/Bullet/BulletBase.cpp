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

	/*�A�j���[�V�����p�������o������*/
	m_anim_timer		= 0;
	m_anim_tex_all		= 16;
	m_anim_tex_width	= 4;
	m_anim_tex_height	= 4;
	m_anim_flame		= 5;

	m_move_count	= 0.f;
	m_move_limit	= 500.f;
	m_speed			= 5.f;

	//���W���w��
	m_pos.y = 500.f;
	m_pos.x = 0.f;
}

void BulletBase::Update()
{
	AnimationUpdate();
}

void BulletBase::Draw()
{
	//���ŏ�Ԃ̏ꍇ�A�`�悵�Ȃ�(�f�o�b�O�p)
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

	if (m_anim_timer >= m_anim_flame) {//�摜��ύX����

		m_anim_timer = 0;

		//���������ڂ����Z
		++m_draw_param.tu;

		//���������ڂ��摜�̕������ȏ�̏ꍇ
		if (m_draw_param.tu > m_anim_tex_width) {

			m_draw_param.tu = 1;

			//�c�������ڂ����Z
			++m_draw_param.tv;

			//�c�������ڂ��摜�̕������ȏ�̏ꍇ
			if (m_draw_param.tv > m_anim_tex_height) {

				m_draw_param.tv = 1;

			}
		}

		//tu��tv����v�Z�������݉����ڂ̃A�j���[�V���������������𒴂��Ă����ꍇ�A
		//tu��tv�����Z�b�g
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
