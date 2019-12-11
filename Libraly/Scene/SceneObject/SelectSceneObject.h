#ifndef SELECTSCENEOBJECT_H_
#define SELECTSCENEOBJECT_H_

#include "SceneBase.h"

class SelectSceneObject :public SceneBase
{
public:
	SelectSceneObject();
	~SelectSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif
