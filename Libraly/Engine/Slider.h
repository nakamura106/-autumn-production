#ifndef SLIDER_H_
#define SLIDER_H_

#include "../Texture/Texture.h"

/** @brief �X���C�_�[�̈ړ����� */
enum SliderDirection
{
	LeftToRight,		//!< �� => �E
	RightToLeft,		//!< �E => ��
	UpToDown,			//!< �� => ��
	DownToUp,			//!< �� => ��
};

/** @brief �X���C�_�[�\���� */
struct Slider
{

	// ���㌴�_
	float X;				//!< �X���C�_�[�`��ʒu(X)
	float Y;				//!< �X���C�_�[�`��ʒu(Y)

	float MinValue;			//!< �ŏ��l
	float MaxValue;			//!< �ő�l

	float CurrentValue;		//!< ���݂̒l
	float NextValue;		//!< ���̒l
	float MoveSpeed;		//!< �ړ����x

	SliderDirection Dir;			//!< �i�s����
	int TextureCategory;	//!< �g�p����e�N�X�`��
	int TextureId;
};

/**
* @brief �X���C�_�[��NextValue�̍X�V�֐�@n
* �X���C�_�[��NextValue���X�V����
* @param[in] next_value �X�V����l
* @param[out] out_slider �X�V����X���C�_�[�f�[�^
*/
void UpdateSliderNextValue(float next_value, Slider& out_slider);

/**
* @brief �X���C�_�[��Current�̍X�V�֐�@n
* �X���C�_�[��CurrentValue���X�V����
* @param[out] out_slider �X�V����X���C�_�[�f�[�^
*/
void UpdateSliderCurrentValue(Slider& out_slider);


/**
* @brief �t�ړ��֐�@n
* �X���C�_�[�̈ړ������Ƃ͔��΂ɓ������߂̏������s��
* @param[in] rate �`�悷��X���C�_�[�̈ʒu�̔䗦
* @param[in] size �X���C�_�[�̃T�C�Y
* @param[out] out_pos �X���C�_�[�̍��W
* @param[out] out_tex_pos �X���C�_�[�摜�̃e�N�X�`�����W
* @param[out] out_size �X���C�_�[�摜�̃e�N�X�`���T�C�Y
*/
void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size);

/**
* @brief �X���C�_�[�`��֐�(��`Version)@n
* �X���C�_�[�\���̂̏�񂩂�X���C�_�[��`�悷��
* @param[in] slider �`��Ɏg���X���C�_�[���
*/

/**
* @brief �X���C�_�[�`��֐�(UV�}�b�s���OVersion)@n
* �X���C�_�[�\���̂̏�񂩂�X���C�_�[��`�悷��
* @param[in] slider �`��Ɏg���X���C�_�[���
*/
void DrawSliderUVMappingVersion(const Slider& slider);

#endif
