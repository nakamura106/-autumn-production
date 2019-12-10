#ifndef UIBASE_H_
#define UIBASE_H_

#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Object/Definition.h"


class UiBase {
public:
	UiBase();
	virtual ~UiBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw();

protected:
	Position m_pos;
	DrawParam m_param;


};

#endif
