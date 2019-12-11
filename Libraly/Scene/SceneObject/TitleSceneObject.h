#ifndef TITLESCENEOBJECT_H_
#define TITLESCENEOBJECT_H_

#include "SceneBase.h"

class TitleSceneObject :public SceneBase
{
public:
	TitleSceneObject();
	~TitleSceneObject();

	void Init()override;
	void Update()override;
	void Draw()override;

private:


};

#endif

