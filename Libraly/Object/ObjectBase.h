#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"
class ObjectBase {
public:
	ObjectBase();
	virtual ~ObjectBase();
	virtual void Update() = 0;
	void Draw();

protected:
	float m_posx, m_posy;
	bool m_is_delete;

};

#endif

