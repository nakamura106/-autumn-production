#ifndef ENDSCENEOBJECT_H_
#define ENDSCENEOBJECT_H_

#include "SceneBase.h"
#include "../../Object/Definition.h"

class EndSceneObject :public SceneBase
{
public:
	EndSceneObject();
	~EndSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Position m_draw_pos[3];
	DrawParam m_param[3];
};

#endif

