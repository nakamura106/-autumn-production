#include"FlameTimer.h"
#include"Graphics.h"
#include<string>

namespace FlameTimer {

	//�t���[�����v���p�^�C�}�[
	int g_flame_timer = 0;

	bool g_can_count = false;

	//�g�p�֎~namespace
	namespace DoNotUse {

		//�^�C�}�[�L����
		void ActiveTimer() {
			g_can_count = true;
		}

		//�J�E���g
		void CountTimer() {

			//�^�C�}�[���L���ł͂Ȃ��ꍇ�Areturn
			if (!g_can_count)return;

			//1�N�Ԃ̌v�����\
			++g_flame_timer;

			//�I�[�o�[�t���[�΍�
			if (g_flame_timer >= 2147483647) {
				g_flame_timer = 0;
			}

			g_can_count = false;

		}
	}


	int GetNowFlame() {

		return g_flame_timer;
	}

	int GetNowFlame(int before_flame_) {

		return (g_flame_timer - before_flame_);
	}

	namespace Debug {

		void DrawTimer() {
			DrawFont(
				50.f,
				250.f,
				std::to_string(g_flame_timer).c_str(),
				FontSize::Large,
				FontColor::Red
			);
		}
	}

}