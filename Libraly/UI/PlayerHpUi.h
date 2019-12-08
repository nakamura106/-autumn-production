#ifndef PLAYERHPUI_H_
#define PLAYERHPUI_H_

#include "UiBase.h"

class PlayerHpUi :public UiBase
{
public:
	PlayerHpUi();
	~PlayerHpUi();

	void Init();
	void Update();
	void Draw();

protected:
	// Player��Hp��Ԃ��擾��������֐�
	void GetPlayerHpState();

private:
	int m_hp_state;	// PlayerHP�̏�Ԃ�񋓌^�ŕۑ�����

};

#endif

