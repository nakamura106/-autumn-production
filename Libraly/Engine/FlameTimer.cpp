#include"FlameTimer.h"
#include"Graphics.h"
#include<string>

namespace FlameTimer {

	//フレーム数計測用タイマー
	int g_flame_timer = 0;

	bool g_can_count = false;

	//使用禁止namespace
	namespace DoNotUse {

		//タイマー有効化
		void ActiveTimer() {
			g_can_count = true;
		}

		//カウント
		void CountTimer() {

			//タイマーが有効ではない場合、return
			if (!g_can_count)return;

			//1年間の計測が可能
			++g_flame_timer;

			//オーバーフロー対策
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