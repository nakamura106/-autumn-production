#include "Slider.h"
// #include "Graphics.h"
// #include "../Texture/Texture.h"
#include <Windows.h>
#include <math.h>


void UpdateSliderNextValue(float next_value, Slider& out_slider)
{
	// �l���X�V����
	out_slider.NextValue = max(out_slider.MinValue, min(next_value, out_slider.MaxValue));

	// ���̒l�ƐV�����l�̍����o���āA���x���Z�o����
	float distance = fabsf(out_slider.CurrentValue - out_slider.NextValue);

	// �ړ��ɂ�����t���[����
	float moev_frame = 60.0f;
	out_slider.MoveSpeed = distance / moev_frame;
}


void UpdateSliderCurrentValue(Slider& out_slider)
{
	// NextValue��CurrentValue�ɍ��������MoveSpeed�ŉ��Z����
	if (out_slider.CurrentValue <= out_slider.NextValue)
	{
		out_slider.CurrentValue = min(out_slider.CurrentValue + out_slider.MoveSpeed, out_slider.NextValue);
	}
	else
	{
		out_slider.CurrentValue = max(out_slider.CurrentValue - out_slider.MoveSpeed, out_slider.NextValue);
	}
}


void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size)
{
	// �䗦����`��J�n�ʒu�����炷
	out_pos = (out_pos + size) - (rate * size);

	// �T�C�Y���䗦�ŕύX����
	out_size *= rate;

	// �e�N�X�`���̍��W���䗦�̕��������炷
	out_tex_pos += (1.0f - rate) * size;
}


void DrawSliderUVMappingVersion(const Slider& slider)
{
	Texture* tex_data = GetTexture(slider.TextureCategory,slider.TextureId);

	// �ύX��������slider��texture_data����擾����
	float pos_x = slider.X;
	float pos_y = slider.Y;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = tex_data->Width;
	float tex_height = tex_data->Height;

	// ����̒l��䗦�Ƃ��ĎZ�o����
	float rate = (slider.CurrentValue - slider.MinValue) / (slider.MaxValue - slider.MinValue);
	// �e�i�s�����ɂ�鏈������������
	if (slider.Dir == SliderDirection::LeftToRight)
	{
		// �����ɔ䗦���|���ăT�C�Y�𒲐�����
		tex_width *= rate;
	}
	else if (slider.Dir == SliderDirection::RightToLeft)
	{
		// �ŏ� => �ő�̕�����X���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}
	else if (slider.Dir == SliderDirection::UpToDown)
	{
		// �c���ɔ䗦���|���ăT�C�Y�𒲐�����
		tex_height *= rate;
	}
	else if (slider.Dir == SliderDirection::DownToUp)
	{
		// �ŏ� => �ő�̕�����Y���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
		ReverseMove(rate, tex_height, pos_y, tex_y, tex_height);
	}

	DrawUVMappingTexture(
		pos_x,
		pos_y,
		tex_data,
		tex_x,
		tex_y,
		tex_width,
		tex_height
	);
}