#ifndef PLAYERHPUI_H_
#define PLAYERHPUI_H_

#include "UiBase.h"

class PlayerHpUi :public UiBase
{
public:
	PlayerHpUi();
	~PlayerHpUi();

	void Init()override;
	void Update()override;
	void Draw()override;

protected:
	// Player��Hp��Ԃ��擾��������֐�
	void GetPlayerHpState();

private:
	int m_hp_state;	// PlayerHP�̏�Ԃ�񋓌^�ŕۑ�����

	const float PLAYERHP_UI_POS_X = 20.0f;
	const float PLAYERHP_UI_POS_Y = 20.0f;

};

#endif

