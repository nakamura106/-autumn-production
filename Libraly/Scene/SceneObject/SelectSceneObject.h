#ifndef SELECTSCENEOBJECT_H_
#define SELECTSCENEOBJECT_H_

#include "SceneBase.h"
#include "../../Object/Definition.h"

class SelectSceneObject :public SceneBase
{
public:
	SelectSceneObject();
	~SelectSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	void BossSelectUpdate();
	void BrassSelectUpdate();

	Position m_pos[9];
	Position m_mouse_pos;
	DrawParam m_param[9];

	bool is_hit_mouse;
	bool is_brass_scene;

};

#endif
