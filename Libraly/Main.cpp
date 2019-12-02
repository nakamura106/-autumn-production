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
	// �G���W���̏�����
	if (InitEngine(1920, 1080, "Sleep Melody") == false)
	{
		return 0;
	}

	//�R�����g�A�E�g���������ƂŃ}�E�X�J�[�\�����������Ƃ��ł��܂�
	//ShowCursor(FALSE);

	//�v���C�X�e�[�V�����ŉ���炷���Ƃ��ł��܂�
	//PlayStation("Sound/Techno_1.wav");

	//���u��


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
			//�^�C�}�[����
			FlameTimer::DoNotUse::ActiveTimer();
			FlameTimer::DoNotUse::CountTimer();

			UpdateScene();

			

		}
	}


	//SoundEnd();

	// �G���W���I��
	EndEngine();

	return 0;
}

