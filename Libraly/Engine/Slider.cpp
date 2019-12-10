#include "Slider.h"
// #include "Graphics.h"
// #include "../Texture/Texture.h"
#include <Windows.h>
#include <math.h>


void UpdateSliderNextValue(float next_value, Slider& out_slider)
{
	// 値を更新する
	out_slider.NextValue = max(out_slider.MinValue, min(next_value, out_slider.MaxValue));

	// 今の値と新しい値の差を出して、速度を算出する
	float distance = fabsf(out_slider.CurrentValue - out_slider.NextValue);

	// 移動にかかるフレーム数
	float moev_frame = 60.0f;
	out_slider.MoveSpeed = distance / moev_frame;
}


void UpdateSliderCurrentValue(Slider& out_slider)
{
	// NextValueとCurrentValueに差があればMoveSpeedで演算する
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
	// 比率から描画開始位置をずらす
	out_pos = (out_pos + size) - (rate * size);

	// サイズも比率で変更する
	out_size *= rate;

	// テクスチャの座標も比率の分だけずらす
	out_tex_pos += (1.0f - rate) * size;
}


void DrawSliderUVMappingVersion(const Slider& slider)
{
	Texture* tex_data = GetTexture(slider.TextureCategory,slider.TextureId);

	// 変更される情報をsliderとtexture_dataから取得する
	float pos_x = slider.X;
	float pos_y = slider.Y;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = tex_data->Width;
	float tex_height = tex_data->Height;

	// 現状の値を比率として算出する
	float rate = (slider.CurrentValue - slider.MinValue) / (slider.MaxValue - slider.MinValue);
	// 各進行方向による処理を実装する
	if (slider.Dir == SliderDirection::LeftToRight)
	{
		// 横幅に比率を掛けてサイズを調整する
		tex_width *= rate;
	}
	else if (slider.Dir == SliderDirection::RightToLeft)
	{
		// 最小 => 最大の方向とX軸の最小 => 最大が逆なので反転させる
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}
	else if (slider.Dir == SliderDirection::UpToDown)
	{
		// 縦幅に比率を掛けてサイズを調整する
		tex_height *= rate;
	}
	else if (slider.Dir == SliderDirection::DownToUp)
	{
		// 最小 => 最大の方向とY軸の最小 => 最大が逆なので反転させる
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