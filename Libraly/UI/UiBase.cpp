#include "UiBase.h"

UiBase::UiBase()
{
	m_param.category_id = TEXTURE_CATEGORY_GAME;
}

UiBase::~UiBase()
{
}

void UiBase::Draw()
{
	// �e�����o�ϐ��̒l�͔h���N���X���Ŏw�肷�邱��
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_param.texture_id));
}
