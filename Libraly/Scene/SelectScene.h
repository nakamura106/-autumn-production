/**
* @file HelpScene.h
* @brief ヘルプシーンの関数の宣言
*/
#ifndef SELECTSCENE_H_
#define SELECTSCENE_H_

#include "Scene.h"

/**
* @brief ヘルプシーンの更新関数@n
* ヘルプシーンの仕様が実行される
* @return 遷移先シーンID(基本はSceneId::HelpSceneが返る)
*/
SceneId UpdateSelectScene();

/**a
* @brief ヘルプシーンの描画関数@n
* ヘルプシーンのオブジェクトを描画するための関数
*/
void DrawSelectScene();

#endif


