#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include "UiBase.h"

class UiManager
{
public:
	static UiManager* Instance();

	void Init();
	void Update();
	void Draw();

protected:
	UiManager();
	~UiManager();

private:
	static UiManager* p_instance;
	static const int MAX_UI_OBJ = 20;

	UiBase* ui_objects[MAX_UI_OBJ];

};

UiManager* UiManager::p_instance = 0;

#endif

