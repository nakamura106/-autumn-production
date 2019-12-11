#ifndef TITLESCENEOBJECT_H_
#define TITLESCENEOBJECT_H_

#include "SceneBase.h"
#include "../../Object/Definition.h"


class TitleSceneObject :public SceneBase
{
public:
	TitleSceneObject();
	~TitleSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

	bool m_help_flag, m_select_flag;

private:
	Position m_mouse_pos;
	Position m_draw_pos[5];
	DrawParam m_param[5];

};

#endif

