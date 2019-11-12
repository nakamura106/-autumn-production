#include "../Engine/Windows.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Engine.h"

bool InitEngine(int width, int height, const char* title_name)
{
	if (MakeWindow(width, height, title_name) == false)
	{
		return false;
	}

	if (InitGraphics() == false)
	{
		return false;
	}

	if (InitInput() == false)
	{
		return false;
	}

	InitTexture();

	return true;
}

void EndEngine()
{
	AllReleaseTexture();
	EndGraphics();
	EndInput();
}
