#include"TrpPlayer.h"

TrpPlayer trpplayer;

TrpPlayer::TrpPlayer()
{
	Init();
}

TrpPlayer::~TrpPlayer()
{

}

void TrpPlayer::Init()
{
	trpplayer.m_is_delete = true;
	trpplayer.m_is_invincible = true;
	trpplayer.m_hp = 0;

}

void TrpPlayer::Create()
{

}

void TrpPlayer::Update()
{

}

void TrpPlayer::Draw()
{

}