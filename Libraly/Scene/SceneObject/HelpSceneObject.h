#ifndef HELPSCENEOBJECT_H_
#define HELPSCENEOBJECT_H_

#include "SceneBase.h"
#include "../../Object/Definition.h"

class HelpSceneObject :public SceneBase
{
public:
	HelpSceneObject();
	~HelpSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Position m_draw_pos[2];
	DrawParam m_param[2];
};

#endif

