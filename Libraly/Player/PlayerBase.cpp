#include"PlayerBase.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include "../Effect/Effects/SweatEffect.h"
#include "../Effect/Effects/DebuffEffect.h"
#include "../Effect/Effects/FailureEffect.h"
#include "../Effect/Effects/LandingEffect.h"
#include "../Effect/Effects/ShotEffect.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Collision/ShapeType/ShapeRect.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/ObjectManager.h"
#include "../Sound/SoundManager.h"


PlayerBase::PlayerBase()
	:ObjectBase(ObjectRavel::Ravel_Player, Direction::RIGHT, P_speed, 0)
{
	//�g�p�摜�ݒ�
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayer_Taiki_RightTex;
	m_draw_param.tex_size_x = G_PLAYER_SIZE;
	m_draw_param.tex_size_y = G_PLAYER_SIZE;

	//�A�j���[�V�����p�������o������
	m_anim_param.split_all = 12;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;
	m_anim_param.change_flame = Dispflame;

	m_effect = (int)P_effect::None;

	m_shape_list.push_back(new ShapeCircle(m_pos.x, 61.0f, m_pos.y, 57.0f, 39.0f, 256.0f));
	m_shape_list.push_back(new ShapeRect(m_pos.x, 61.0f, m_pos.y, 144.0f, 61.0f, 94.0f, 256.0f));
	m_shape_list.push_back(new ShapeCircle(m_pos.x, 65.0f, m_pos.y, 222.0f, 26.0f, 256.0f));
	

	m_animtimer = 0;
	m_floorpos = P_posYforest;
	m_effecttimer = 16;
	m_gravity = 17.0f;
	m_is_miss = false;
	m_is_hit_mapobj = false;
	AllInitEffect();

}

PlayerBase::~PlayerBase()
{
	//bullet���
	for (auto& i : bullet_list) {
		delete i;
		i = nullptr;
	}
	std::vector<PlayerBullet*>().swap(bullet_list);
}
void PlayerBase::Create()
{

}

void PlayerBase::Update()
{
	ObjectBase::Update();
	BulletControl();
	if (DataBank::Instance()->GetWavetype(WaveType::Wave1)!=true || DataBank::Instance()->GetWavetype(WaveType::Wave2)!=true || DataBank::Instance()->GetWavetype(WaveType::Wave3)!=true)
	{
		P_Controll();
	}
	AnimationUpdate();
	ChangeState();
	Atkjudge();


	CollisionParamUpdate();


	AllUpdateEffect();

	DataBank::Instance()->SetPlayerHp(m_hp);
	DataBank::Instance()->SetPlayerMapPos(m_map_pos);
	DataBank::Instance()->SetNote(notebox[0], notebox[1], notebox[2]);
	DataBank::Instance()->SetPlayerDirection(m_direction);
	

	if (GetKey(E_KEY) == true)
	{
		DataBank::Instance()->SetWave(WaveType::Wave1, true);
	}

	

}

void PlayerBase::BulletControl()
{
	for (int i = 0; i < static_cast<int>(bullet_list.size()); ++i) {
		//�e�̍X�V
		bullet_list[i]->Update();

		//�e��is_delete��true�̏ꍇ�A�e����
		if (bullet_list[i]->GetIsDelete()) {
			//���������
			delete bullet_list[i];

			//�e������
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}

void PlayerBase::Draw()
{
	
	ObjectBase::Draw();

	for (const auto& i : bullet_list) {

		if (i != nullptr) {
			i->Draw();
		}

	}

	AllDrawEffect();

}

void PlayerBase::P_Controll()
{
	if (m_play_note_timer <= 70)
	{
		m_play_note_timer++;
	}

	if (m_effecttimer <= 16)
	{
		m_effecttimer++;
	}
	
	DataBank::Instance()->SetState(m_state);

	/*�{�^���𗣂�����Ƀ��[�V������
	�p�����Ă��܂�Ȃ��悤�ɂ��鏈��*/
	if (m_is_active == true)
	{
		m_is_active = false;
	}
	
	// ���܂Ń{�^������


	if (GetKey(A_KEY) == true)
	{
		ChangeSceneStep(SceneStep::EndStep);
	}


	//�E�ړ�
	if (GetKey(RIGHT_KEY) == true&&m_state!=(int)P_State::Attack)
	{
		m_state = (int)P_State::Move;
		DataBank::Instance()->SetState(m_state);
		if (DataBank::Instance()->GetfgPos() >= 0 || DataBank::Instance()->GetfgPos() <= -3550.0f )
		{
			m_pos.x += m_speed;
		}
		if (m_direction == LEFT) {
			m_pos.x += lrAdjustment;
		}
		if (m_map_pos < 3550.0f)
		{
			m_map_pos += m_speed;
		}

		
			m_direction = RIGHT;
		
			
		

		m_is_active = true;
	}

	//���ړ�
	else if (GetKey(LEFT_KEY) == true && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Move;
		DataBank::Instance()->SetState(m_state);
		if (DataBank::Instance()->GetfgPos() <= -3550.0f || DataBank::Instance()->GetfgPos() >= 0)
		{
			m_pos.x -= m_speed;
		}
		if (m_direction == RIGHT) {
			m_pos.x -= lrAdjustment;
		}
		if (m_map_pos > 0.0f)
		{
			m_map_pos -= m_speed;
		}
		
		m_direction = LEFT;
		
		m_is_active = true;
	}

	//�W�����v����
	if (GetKeyDown(SPACE_KEY) == true&& m_do_jump != true)
	{
		m_do_jump = true;
		m_is_active = true;
		m_gravity = -P_jump_power;
		InitAllState();
	}
	if (m_is_hit_mapobj==true&&m_do_jump!=true)
	{
		m_pos.y = m_floorpos;
	}
	
	//�����Z���؂�ւ�����(�����Ă���Ԃ̂�)
	if (GetKey(SHIFT_KEY) == true)
	{
		m_Key = (int)Key::Minor;
	}
	else
	{
		m_Key = (int)Key::Major;
	}

	//��������
	if (GetKey(ONE_KEY) == true)
	{
		if (m_play_note_timer >= 70 && m_Key == (int)Key::Major)
		{
			m_play_note[0] = true;
			m_play_note_timer = 0;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					break;
				}
			}
		}
		if (m_play_note_timer >= 70 && m_Key == (int)Key::Minor)
		{
			m_play_note[1] = true;
			m_play_note_timer = 0;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = B;
					break;
				}
			}
		}
	}

	// ��
	
	
	//active��false�Ȃ�ҋ@��Ԃɂ��鏈��
	if (m_is_active == false&& m_state != (int)P_State::Wait)
	{	
		m_state = (int)P_State::Wait;
		DataBank::Instance()->SetState(m_state);
	}

	if (m_do_jump == true)
	{
		Jump();
	}
	//�v���C���[���W�����v���Ă��邩���肷��(���Ă���Ȃ�W�����v�֐����Ăяo��)
	if (m_is_animation_end == true)
	{
		m_anim_param.split_all = 12;
		m_anim_param.split_height = 4;
	}

	if (m_do_attack == true)
	{
		m_animtimer++;
		Attack();
	}

	//��ʒ[�Ƃ̓����蔻��
	if (m_pos.x <= -lrAdjustment - 7)
	{
		m_pos.x += m_speed;
	}

	if (m_pos.x >= 1800.0f)
	{
		m_pos.x -= m_speed;
	}

	//�v���C���[�ɏd�͂������鏈��
	
	if (m_is_hit_mapobj==false)
	{
		m_pos.y += m_gravity;
		m_gravity += Gravity;
	}

	if (m_pos.y > P_posYforest) {
		m_pos.y = P_posYforest;
	}
	

	m_is_hit_mapobj = false;
}

void PlayerBase::CreateBullets(PlayerBulletType bullettype)
{
	Position b_pos;
	if (m_direction == Direction::LEFT) {
		b_pos.x = m_map_pos - m_draw_param.tex_size_x/2.0f;
		b_pos.y = m_pos.y;
	}
	else {
		b_pos.x = m_map_pos + m_draw_param.tex_size_x/2.0f;
		b_pos.y = m_pos.y;
	}

	//Bullet(�e)����

	bullet_list.push_back(new PlayerBullet(b_pos.x, b_pos.y, M_BULLET_SPEED, (Direction)m_direction, bullettype));

}

void PlayerBase::Atkjudge()
{
	if (notebox[0] == A && notebox[1] == A && notebox[2] == A || notebox[0] == A && notebox[1] == B && notebox[2] == A)
	{

		if (m_is_release == false)
		{
			m_release_timer++;
		}
		if (notebox[1] == A)
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//�e����
				CreateBullets(PlayerBulletType::Chocho_1);
				m_do_attack = true;
				m_is_active = true;
				InitAllState();
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
		else
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//�e����
				CreateBullets(PlayerBulletType::Chocho_2);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
	}

	if (notebox[0] == B && notebox[1] == B && notebox[2] == B || notebox[0] == B && notebox[1] == A && notebox[2] == B)
	{

		if (m_is_release == false)
		{
			m_release_timer++;
		}
		if (notebox[1] == B)
		{


			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//�e����
				CreateBullets(PlayerBulletType::Tancho_1);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
		else
		{
			if (!m_do_bullet_firing)
			{
				m_do_bullet_firing = true;
				//�e����
				CreateBullets(PlayerBulletType::Tancho_2);
				m_do_attack = true;
				m_is_active = true;
			}
			if (m_release_timer >= 140)
			{
				m_is_release = true;
				ReleaseNote();
			}
		}
	}

	if (notebox[0] == A && notebox[1] == A && notebox[2] == B || notebox[0] == A && notebox[1] == B && notebox[2] == B ||
		notebox[0] == B && notebox[1] == B && notebox[2] == A || notebox[0] == B && notebox[1] == A && notebox[2] == A)
	{
		
		if (m_is_release == false)
		{
			m_is_miss = true;
			m_release_timer++;

		}
		if (m_release_timer >= 140)
		{
			m_is_miss = false;
			m_is_release = true;
			ReleaseNote();
		}	
	}
}

void PlayerBase::ReleaseNote()
{
	m_release_timer = 0;

	//�����̉��t(�X�g�b�N)�����ׂĔj������
	for (int i = 0; i < 3; i++)
	{
		notebox[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		m_play_note[i] = false;
	}
	m_do_bullet_firing = false;

	m_is_release = false;

}

void PlayerBase::Jump()
{
	static float jump_power = P_jump_power;

	//�v���C���[��Damage��ԁAAttack��ԂłȂ���΃W�����v��Ԃɂ���
	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump;
		DataBank::Instance()->SetState(m_state);
	}
	if (m_do_jump == true && m_state == (int)P_State::Attack)
	{
		m_state = (int)P_State::Jump_Attack;
		DataBank::Instance()->SetState(m_state);
	}
	if (m_do_jump == true && m_state == (int)P_State::Damage)
	{
		m_state = (int)P_State::Jump_Damage;
		DataBank::Instance()->SetState(m_state);
	}


	//�v���C���[���n��(�W�����v�J�n�O��Y���W)�ɂ�����W�����v��Ԃ���������
	if (m_pos.y >=m_floorpos)
	{
		m_effecttimer = 0;
		
		
		m_do_jump = false;
		m_is_active = false;
	}
}

void PlayerBase::Attack()
{
	if (m_animtimer >= 72)
	{
		m_do_attack = false;
		m_is_active = false;
		m_animtimer = 0;
	}
	if (GetKey(LEFT_KEY) == true || GetKey(RIGHT_KEY) == true)
	{
		if (m_state != (int)P_State::Damage && m_state != (int)P_State::Attack)
		{
			m_state = (int)P_State::Move_Attack;
			DataBank::Instance()->SetState(m_state);
		}
	}
	else if (m_state != (int)P_State::Damage&&m_state!=(int)P_State::Attack )
	{
		m_state = (int)P_State::Attack;
		DataBank::Instance()->SetState(m_state);
	}
	
}

void PlayerBase::AllInitEffect()
{
	m_effect_list.push_back(new SweatEffect(this));
	m_effect_list.push_back(new DebuffEffect(this));
	m_effect_list.push_back(new FailureEffect(this));
	m_effect_list.push_back(new LandingEffect(this));
	m_effect_list.push_back(new ShotEffect(this));
}

void PlayerBase::AllUpdateEffect()
{
	// �G�t�F�N�g����
	// HP�P�̎��̃G�t�F�N�g����
	if (m_hp == 1) {
		m_effect_list.at(0)->WakeUp();
	}
	else {
		m_effect_list.at(0)->Sleep();
	}
	//���t���s��
	if (m_is_miss==true)
	{
		m_effect_list.at(2)->WakeUp();
	}
	else
	{
		m_effect_list.at(2)->Sleep();
	}
	//���n��
	if (m_effecttimer <= 15)
	{
		m_effect_list.at(3)->WakeUp();
	}
	else
	{
		m_effect_list.at(3)->Sleep();
	}
	// ��e���G�t�F�N�g����
	if (m_state == (int)P_State::Damage)
	{
		m_effect_list.at(4)->WakeUp();
	}
	else 
	{
		m_effect_list.at(4)->Sleep();
	}



	m_effect_list.at(0)->Update();
	m_effect_list.at(1)->Update();
	m_effect_list.at(2)->Update();
	m_effect_list.at(3)->Update();
	m_effect_list.at(4)->Update();
}

void PlayerBase::AllDrawEffect()
{
		m_effect_list.at(0)->Draw();
		m_effect_list.at(1)->Draw();
		m_effect_list.at(2)->Draw();
		m_effect_list.at(3)->Draw();
		m_effect_list.at(4)->Draw();
}

void PlayerBase::CollisionParamUpdate()
{
	for (const auto& i : m_shape_list)
	{
		i->Update(m_pos.x, m_pos.y, m_direction);
	}
	CollisionManager::GetInstance().AddPlayerColObject(this);
}

void PlayerBase::InitWaitState() 
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Taiki_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Taiki_RightTex;
	}
}

void PlayerBase::InitMoveState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Walk_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Walk_RightTex;
	}

}

void PlayerBase::InitJumpState() 
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Jump_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Jump_RightTex;
	}
}

void PlayerBase::InitJumpAttackState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_JumpAttack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_JumpAttack_RightTex;
	}
}

void PlayerBase::InitJumpDamageState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_JumpDamage_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_JumpDamage_RightTex;
	}
}

void PlayerBase::InitDamageState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Damage_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Damage_RightTex;
	}
}

void PlayerBase::InitAttackState()
{
	
	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Attack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Attack_RightTex;
	}
}

void PlayerBase::InitMoveAttackState()
{

	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_WalkAttack_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_WalkAttack_RightTex;
	}
}

void PlayerBase::InitThinkState()
{
	
	if (m_direction == Direction::LEFT)
	{
		
	}
	if (m_direction == Direction::RIGHT)
	{

	}
}

void PlayerBase::InitDeathState()
{
	
	if (m_direction == Direction::LEFT)
	{
	
	}
	if (m_direction == Direction::RIGHT)
	{

	}
}

void PlayerBase::InitClearState()
{

	if (m_direction == Direction::LEFT)
	{
		m_draw_param.texture_id = GamePlayer_Clear_LeftTex;
	}
	if (m_direction == Direction::RIGHT)
	{
		m_draw_param.texture_id = GamePlayer_Clear_RightTex;
	}
}

void PlayerBase::ChangeState()
{
	

	switch (m_state)
	{
	case (int)P_State::Wait:
		InitWaitState();
		break;
	case (int)P_State::Move:
		InitMoveState();
		break;
	case (int)P_State::Jump:
		InitJumpState();
		break;
	case (int)P_State::Attack:
		InitAttackState();
		break;
	case (int)P_State::Move_Attack:
		InitMoveAttackState();
		break;
	case (int)P_State::Damage:
		InitDamageState();
		break;
	case (int)P_State::Jump_Damage:
		InitJumpDamageState();
		break;
	case (int)P_State::Jump_Attack:
		InitJumpAttackState();
		break;
	case (int)P_State::Clear:
		InitClearState();
		break;
	case (int)P_State::Death:
		InitDeathState();
		break;	
	default:
		break;
	}

	
}

void PlayerBase::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{
	if (ravel_ == ObjectRavel::Ravel_MapObj && 
		m_pos.y + 128.0f <= hit_use_atk_) {

		m_floorpos = hit_use_atk_;

		m_pos.y = m_floorpos - m_draw_param.tex_size_y/2.f;

		m_is_hit_mapobj = true;

	}

}

void PlayerBase::InitAllState()
{
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
}

