#ifndef SCENEBASE_H_
#define SCENEBASE_H_

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

private:

};

#endif

