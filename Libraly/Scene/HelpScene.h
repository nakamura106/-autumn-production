/**
* @file HelpScene.h
* @brief ヘルプシーンの関数の宣言
*/
#ifndef HELPSCENE_H_
#define HELPSCENE_H_

#include "Scene.h"

/**
* @brief ヘルプシーンの更新関数@n
* ヘルプシーンの仕様が実行される
* @return 遷移先シーンID(基本はSceneId::HelpSceneが返る)
*/
SceneId UpdateHelpScene();

/**a
* @brief ヘルプシーンの描画関数@n
* ヘルプシーンのオブジェクトを描画するための関数
*/
void DrawHelpScene();

#endif

