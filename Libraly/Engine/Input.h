
/**
* @file Input.h
* @brief 入力に関する関数、定数の宣言
*/
#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#include "../Engine/Vec.h"

// キー情報GetKeyシリーズの関数で使用する
#define CLEAR_KEY	0x0000		// キークリア用
#define UP_KEY		0x0001		// 上キー
#define DOWN_KEY	0x0002		// 下キー
#define LEFT_KEY	0x0004		// 左キー
#define RIGHT_KEY	0x0008		// 右キー
#define RETURN_KEY	0x0010		// リターンキー
#define ONE_KEY 	0x0020		// 1キー
#define TWO_KEY		0x0040		// 2キー
#define THREE_KEY	0x0080		// 3キー
#define SHIFT_KEY	0x0100		// Shiftキー
#define SPACE_KEY   0x0200      // SPACEキー
#define A_KEY		0x0400		// Aキー	
#define E_KEY		0x0800		// Eキー

/** @brief マウスボタンの種類 */
enum MouseButton
{
	Left,		//!< 左
	Right,		//!< 右
	Center,		//!< 真ん中
};

/** @brief キーボタンの種類 */
enum ButtonKind
{
	AButton,
	BButton,
	XButton,
	YButton,
	UpButton,
	DownButton,
	LeftButton,
	RightButton,
	ButtonKindMax,
};

enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};

/**
* @brief Input機能初期化関数@n
* デバイスの入力取得に必要な初期化を行う
* ※InitEngineで実行されるので開発側が実行する必要はない
* @return 初期化結果(成功はtrue)
*/
bool InitInput();

/**
* @brief Input機能終了関数@n
* Input機能を終了させる@n
* ※EndEngineで実行されるので開発側が実行する必要はない
*/
void EndInput();

/**
* @brief 入力情報の更新@n
* デバイスの入力情報の更新を行う@n
* 毎フレームに１度必ず実行する必要がある
*/
void UpdateInput();

/**
* @brief クリックした瞬間判定関数@n
* 指定したマウスのボタンがクリックされた瞬間かどうかを判定する
* @return 判定結果(押された瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMouseDown(MouseButton button_type);

/**
* @brief クリック中判定関数@n
* 指定したマウスのボタンがクリック中かどうかを判定する
* @return 判定結果(クリック中瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMousePush(MouseButton button_type);

/**
* @brief クリック終了判定関数@n
* 指定したマウスのボタンがクリックを終了した瞬間かどうかを判定する
* @return 判定結果(クリックをやめた瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMouseUp(MouseButton button_type);

/** @brief マウスの座標取得関数 */
Vec2 GetMousePos();

bool CreateKeyboardDevice();
void UpDateKey();
bool GetKey(DWORD key_code);
bool GetKeyDown(DWORD key_code);
bool GetKeyUp(DWORD key_code);

bool IsButtonPush(ButtonKind button);
bool IsButtonUp(ButtonKind button);
bool IsButtonDown(ButtonKind button);

#endif


