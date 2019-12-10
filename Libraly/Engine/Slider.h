#ifndef SLIDER_H_
#define SLIDER_H_

#include "../Texture/Texture.h"

/** @brief スライダーの移動方向 */
enum SliderDirection
{
	LeftToRight,		//!< 左 => 右
	RightToLeft,		//!< 右 => 左
	UpToDown,			//!< 上 => 下
	DownToUp,			//!< 下 => 上
};

/** @brief スライダー構造体 */
struct Slider
{

	// 左上原点
	float X;				//!< スライダー描画位置(X)
	float Y;				//!< スライダー描画位置(Y)

	float MinValue;			//!< 最小値
	float MaxValue;			//!< 最大値

	float CurrentValue;		//!< 現在の値
	float NextValue;		//!< 次の値
	float MoveSpeed;		//!< 移動速度

	SliderDirection Dir;			//!< 進行方向
	int TextureCategory;	//!< 使用するテクスチャ
	int TextureId;
};

/**
* @brief スライダーのNextValueの更新関数@n
* スライダーのNextValueを更新する
* @param[in] next_value 更新する値
* @param[out] out_slider 更新するスライダーデータ
*/
void UpdateSliderNextValue(float next_value, Slider& out_slider);

/**
* @brief スライダーのCurrentの更新関数@n
* スライダーのCurrentValueを更新する
* @param[out] out_slider 更新するスライダーデータ
*/
void UpdateSliderCurrentValue(Slider& out_slider);


/**
* @brief 逆移動関数@n
* スライダーの移動方向とは反対に動くための処理を行う
* @param[in] rate 描画するスライダーの位置の比率
* @param[in] size スライダーのサイズ
* @param[out] out_pos スライダーの座標
* @param[out] out_tex_pos スライダー画像のテクスチャ座標
* @param[out] out_size スライダー画像のテクスチャサイズ
*/
void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size);

/**
* @brief スライダー描画関数(矩形Version)@n
* スライダー構造体の情報からスライダーを描画する
* @param[in] slider 描画に使うスライダー情報
*/

/**
* @brief スライダー描画関数(UVマッピングVersion)@n
* スライダー構造体の情報からスライダーを描画する
* @param[in] slider 描画に使うスライダー情報
*/
void DrawSliderUVMappingVersion(const Slider& slider);

#endif
