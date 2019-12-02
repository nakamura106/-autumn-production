#include <Windows.h>
#include "../Libraly/Engine/Engine.h"
#include "../Libraly/Scene/Scene.h"
#include "../Libraly/Texture/Texture.h"
#include "../Libraly/Engine/Input.h"
#include "../Libraly/Engine/Graphics.h"
#include "../Libraly/Engine/Sound.h"
#include "../Libraly/Engine/FlameTimer.h"


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	// エンジンの初期化
	if (InitEngine(1920, 1080, "Sleep Melody") == false)
	{
		return 0;
	}

	//コメントアウトを消すことでマウスカーソルを消すことができます
	//ShowCursor(FALSE);

	//プレイステーションで音を鳴らすことができます
	//PlayStation("Sound/Techno_1.wav");

	//仮置き


	while (true)
	{
		bool message_ret = false;
		MSG msg;


		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//タイマー動作
			FlameTimer::DoNotUse::ActiveTimer();
			FlameTimer::DoNotUse::CountTimer();

			UpdateScene();

			

		}
	}


	//SoundEnd();

	// エンジン終了
	EndEngine();

	return 0;
}

