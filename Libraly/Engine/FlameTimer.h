#pragma once


namespace FlameTimer {

	/*���g�p�֎~�I��*/
	namespace DoNotUse {
		void ActiveTimer();
		void CountTimer();
	}
	/*���g�p�֎~��*/

	//���݂̌o�߃t���[�����Q�b�^�[
	int GetNowFlame();

	//���݂̃^�C�}�[�t���[��-�����œn�����t���[���Q�b�^�[
	int GetNowFlame(int before_flame_);

	namespace Debug {
		void DrawTimer();
	}

}