#pragma once

#include"../Object/ObjectBase.h"
#include"../Object/Definition.h"





class Map:public ObjectBase
{
public:
	Map();
	~Map();
	//!< �������֐�(���W�Ȃ�)
	void Init()override;
	//!< �摜�Ǎ��֐��֐�
	
	//!< �X�V�֐�(���t���[���X�V���K�v�Ȃ��̓�)
	void Update()override;
	//!< �`��p�֐�(�w�i��I�u�W�F�N�g��`�悷��)
	virtual void Draw()override;
	//!< ���g�p
	void Create(){}



	

private:

	//!< �}�b�v�X�N���[���֐�(�v���C���[�̓����ɍ��킹�ăX�N���[�����x���Ⴄ)
	void MapScroll(int direction_);

	void WaveChange(float enemyX_);

	//!< �����蔻��֐�(�v���C���[���I�u�W�F�N�g�ɓ������Ă��邩���肷��֐�)
	void HitJudgement();

protected:
	float floor1;
	float floor2;
	float obj[10];



	



};

class Fg :public Map
{
public:
	//!< �������֐�(���W�Ȃ�)
	void Init()override;
	//!< �摜�Ǎ��֐��֐�
	virtual void Load();
	//!< �X�V�֐�(���t���[���X�V���K�v�Ȃ��̓�)
	void Update()override;
	//!< �`��p�֐�(�w�i��I�u�W�F�N�g��`�悷��)
	virtual void Draw()override;
	//!< ���g�p
	void Create() {}

	

private:
	void MapScroll(int direction_);
	void WaveChange(float enemyX_);
protected:
	float fg;
};

