#pragma once


namespace FlameTimer {

	/*↓使用禁止！↓*/
	namespace DoNotUse {
		void ActiveTimer();
		void CountTimer();
	}
	/*↑使用禁止↑*/

	//現在の経過フレーム数ゲッター
	int GetNowFlame();

	//現在のタイマーフレーム-引数で渡したフレームゲッター
	int GetNowFlame(int before_flame_);

	namespace Debug {
		void DrawTimer();
	}

}