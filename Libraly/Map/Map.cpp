#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Player/TrpPlayer.h"





Map::Map()
{
	
}

Map::~Map()
{

}

void Map::Init()
{
	bg.m_pos.x = 0;
	bg.m_pos.y = 0;
	bg.m_speed = 0;
	floor1.m_pos.x = 0;
	floor1.m_pos.y = 0;
	floor1.m_speed = 0;
	floor2.m_pos.x = 0.0f;
	floor2.m_pos.y = 0;
	floor2.m_speed = 0;
	fg.m_pos.x = 0;
	fg.m_pos.y = 0;
	fg.m_speed = 0;
	for (int i = 0; i < 3; i++)
	{
		obj[i].m_pos.x = 500.0f;
		obj[i].m_pos.y = P_posY;
		obj[i].m_speed = 0;
	}
	Load();
}

void Map::Load()
{
	//�}�b�v
	LoadTexture("Res/Tex/Map/�C/sea1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);		//��
	LoadTexture("Res/Tex/Map/�C/sea2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	//�肷��
	LoadTexture("Res/Tex/Map/�C/sea3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	//�l��
	LoadTexture("Res/Tex/Map/�C/sea4.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);		//�C
	
	
	LoadTexture("Res/Tex/Map/�X/Grass Small.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject);
	LoadTexture("Res/Tex/Map/�X/Grass Medium.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject2);
	LoadTexture("Res/Tex/Map/�X/Grass Large.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject3);
}

void Map::Update()
{
	//�E�L�[���������Ƃ��X�N���[���֐��ɉE����(�X�N���[������)�𑗂�
	if (GetKey(RIGHT_KEY) == true)
	{
		MapScroll(RIGHT);
	}
	//���L�[���������Ƃ��X�N���[���֐��ɍ�����(�X�N���[������)�𑗂�
	if (GetKey(LEFT_KEY) == true)
	{
		MapScroll(LEFT);
	}
	HitJudgement();
}

void Map::MapScroll(int direction_)
{
	//�������E�������}�b�v�̒[��-3800�ȏ�̎��ɃX�N���[������
	if (player.Getpos() &&direction_==RIGHT&&fg.m_pos.x >= -3800.0f)
	{
		obj[0].m_pos.x -= P_speed;
		floor1.m_pos.x -= P_speed;
		floor2.m_pos.x -= 3.0f;
		fg.m_pos.x -= P_speed * 2;
	}
	//���������������}�b�v�̒[��0�ȉ��̎��ɃX�N���[������
	if (direction_==LEFT&&fg.m_pos.x < 0.0f)
	{
		obj[0].m_pos.x += P_speed;
		floor1.m_pos.x += P_speed;
		floor2.m_pos.x += 3.0f;
		fg.m_pos.x += P_speed * 2;
	}
}

void Map::HitJudgement()
{
	
}

void Map::Draw()
{
	DrawTexture(bg.m_pos.x, bg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2.m_pos.x, floor2.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1.m_pos.x, floor1.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
	DrawTexture(fg.m_pos.x, fg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
	DrawTexture(obj[0].m_pos.x, obj[0].m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
}