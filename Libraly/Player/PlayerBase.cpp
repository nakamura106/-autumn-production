#include"PlayerBase.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"

PlayerBase::PlayerBase()
	:ObjectBase(ObjectRavel::Ravel_Player,Direction::RIGHT,P_speed)
{
	//�g�p�摜�ݒ�
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayer_Taiki_RightTex;
	m_draw_param.tex_size_x = M_PLAYER_ANIMATION;
	m_draw_param.tex_size_y = M_PLAYER_ANIMATION;

	//�A�j���[�V�����p�������o������
	m_anim_param.split_all = 12;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;
	m_anim_param.change_flame = Dispflame;
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
	P_Controll();
	AnimationUpdate();
	

	DataBank::Instance()->SetPlayerHp(m_hp);
	DataBank::Instance()->SetPlayerMapPos(m_map_pos);
	DataBank::Instance()->SetNote(notebox[0], notebox[1], notebox[2]);

	
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
}

void PlayerBase::P_Controll()
{
	if (m_note_timer <= 70)
	{
		m_note_timer++;
	}


	/*�{�^���𗣂�����Ƀ��[�V������
	�p�����Ă��܂�Ȃ��悤�ɂ��鏈��*/
	if (m_is_active == true)
	{
		m_is_active = false;
	}

	// ���܂Ń{�^������



	//�E�ړ�
	if (GetKey(RIGHT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		if (DataBank::Instance()->GetfgPos() >= 0 || DataBank::Instance()->GetfgPos() <= -3550.0f)
		{
			m_pos.x += m_speed;
		}
		if (m_direction == LEFT) {
			m_pos.x += lrAdjustment;
			//m_map_pos += lrAdjustment;
		}
		if (m_map_pos < 3550.0f)
		{
			m_map_pos += m_speed;
		}
		m_direction = RIGHT;

		m_is_active = true;
	}

	//���ړ�
	else if (GetKey(LEFT_KEY) == true)
	{
		m_state = (int)P_State::Move;
		if (DataBank::Instance()->GetfgPos() <= -3550.0f || DataBank::Instance()->GetfgPos() >= 0)
		{
			m_pos.x -= m_speed;
		}
		if (m_direction == RIGHT) {
			m_pos.x -= lrAdjustment;
			//m_map_pos -= lrAdjustment;
		}
		if (m_map_pos > 0.0f)
		{
			m_map_pos -= m_speed;
		}
		m_direction = LEFT;

		m_is_active = true;
	}

	//�W�����v����
	if (GetKey(SPACE_KEY) == true)
	{
		m_do_jump = true;
		m_is_active = true;
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
		if (m_note_timer >= 70 && m_Key == (int)Key::Major)
		{
			m_play_note[0] = true;
			m_note_timer = 0;
			for (int i = 0; i < 3; i++)
			{
				if (notebox[i] == 0)
				{
					notebox[i] = A;
					break;
				}
			}
		}
		if (m_note_timer >= 70 && m_Key == (int)Key::Minor)
		{
			m_play_note[1] = true;
			m_note_timer = 0;
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
	if (m_is_active == false)
	{
		m_state = (int)P_State::Wait;
	}

	//�v���C���[���W�����v���Ă��邩���肷��(���Ă���Ȃ�W�����v�֐����Ăяo��)
	if (m_do_jump == true)
	{
		Jump();
	}

	if (m_do_attack == true)
	{
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
	if (m_pos.y <= P_posX)
	{
		m_pos.y += Gravity;
	}
}

void PlayerBase::CreateBullets(PlayerBulletType bullettype)
{
	Position b_pos;
	if (m_direction == Direction::LEFT) {
		b_pos.x = m_map_pos - m_draw_param.tex_size_x;
		b_pos.y = m_pos.y;
	}
	else {
		b_pos.x = m_map_pos + m_draw_param.tex_size_x;
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
			m_release_timer++;
		}
		if (m_release_timer >= 140)
		{
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
	}

	m_pos.y -= jump_power;
	jump_power -= Gravity;

	//�v���C���[���n��(�W�����v�J�n�O��Y���W)�ɂ�����W�����v��Ԃ���������
	if (m_pos.y >= P_posYforest)
	{
		jump_power = P_jump_power;
		m_do_jump = false;
		m_is_active = false;
	}
}

void PlayerBase::Attack()
{
	if (m_i > 10)
	{
		m_do_attack = false;
		m_is_active = false;
	}

	if (m_state != (int)P_State::Damage && m_state != (int)P_State::Jump)
	{
		m_state = (int)P_State::Attack;
	}
}