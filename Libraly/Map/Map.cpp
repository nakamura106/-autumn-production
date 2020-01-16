#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Player/TrpPlayer.h"
#include"../Manager/ObjectManager.h"





Map::Map()
{
	m_obj_ravel = ObjectRavel::Ravel_Map;
}

Map::~Map()
{

}

void Map::Init()
{
	
	floor1 = 0;
	floor2 = 0;
	obj[0] = 400.0f;
	obj[1] = 1200.0f;
	obj[2] = 2000.f;
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;
	
	Load();
}

void Map::Load()
{
	//�}�b�v
	LoadTexture("Res/Tex/Map/�X/Woods2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	    //Stage1Bg2
	LoadTexture("Res/Tex/Map/�X/Woods3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	//Stage1Bg3
	LoadTexture("Res/Tex/Map/�X/Woods4.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);		    //Stage1Bg4
	
	
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
	
	DataBank::Instance()->Setfloor1Pos(floor1);
}

void Map::MapScroll(int direction_)
{
	//�������E�������}�b�v�̒[��-3800�ȏ�̎��ɉE�ɃX�N���[������
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen&& direction_==RIGHT&& DataBank::Instance()->GetfgPos()>=-3550.0f )
	{
		
		floor1 -= P_speed;
		obj[0] -= P_speed;
		obj[1] -= P_speed;
		obj[2] -= P_speed;
		floor2 -= floor2speed;
	}
	//���������������}�b�v�̒[��0�ȉ��̎��ɍ��ɃX�N���[������
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen&&direction_==LEFT&&DataBank::Instance()->GetfgPos()<0.0f&&floor1<0.0f&&floor2<0)
	{
		floor1 += P_speed;
		obj[0] += P_speed;
		obj[1] += P_speed;
		obj[2] += P_speed;
		floor2 += floor2speed;
	}
}

void Map::HitJudgement()
{
	
}

void Map::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
	DrawTexture(obj[0], P_posYforest, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
	DrawTexture(obj[1], P_posYforest - 100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject2));
	DrawTexture(obj[2], P_posYforest - 100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
	
	
}

void Fg::Init()
{
	fg = 0;
	
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;

	Load();
}

void Fg::Load()
{
	//�}�b�v
	LoadTexture("Res/Tex/Map/�X/Woods1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);		//��

}

void Fg::Update()
{
	DataBank::Instance()->SetfgPos(fg);
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
	
	
	
}

void Fg::MapScroll(int direction)
{
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen && direction==RIGHT&& fg >= -3550.0f)
	{
		fg -= P_speed * 2;
	}
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen && direction==LEFT&& fg < 0.0f)
	{
		fg += P_speed * 2;
	}
}

void Fg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}