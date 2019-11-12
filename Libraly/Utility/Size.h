/**
* @file Size.h
* @brief �f�[�^�̃T�C�Y(���A�c)��ۑ��ł���\���̂̐錾
*/
#ifndef SIZE_H_
#define SIZE_H_

//=====================================================================//
//! �T�C�Y�f�[�^�p�\����
//=====================================================================//
struct Size
{
	/** Constructor */
	Size()
	{
		Width = 0.0f;
		Height = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] width ����
	* @param[in] height �c��
	*/
	Size(float width, float height)
	{
		Width = width;
		Height = height;
	}

	/**
	* @brief Constructor
	* @param[in] size �R�s�[�p�T�C�Y�f�[�^
	*/
	Size(const Size& size)
	{
		this->Width = size.Width;
		this->Height = size.Height;
	}

	float Width;		//!< ����
	float Height;		//!< �c��
};

#endif

