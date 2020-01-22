#ifndef TITLESCENEOBJECT_H_
#define TITLESCENEOBJECT_H_

#include "SceneBase.h"
#include "../../Object/Definition.h"

enum class TitleSceneState
{
	Home,
	Start,
	Continue,
	Help,

	TitleSceneStateMax,
};


class TitleSceneObject :public SceneBase
{
public:
	TitleSceneObject();
	~TitleSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

	// �^�C�g�����̃V�[���J�ڂ��Ƃ̃A�b�v�f�[�g�֐�
	void UpdateHomeScene();
	void UpdateStartScene();
	void UpdateContinueScene();
	void UpdateHelpScene();

	void UpdateSelectSE();


private:
	Position m_mouse_pos;
	Position m_draw_pos[8];
	DrawParam m_param[8];

	TitleSceneState m_scene_state;

};

#endif

