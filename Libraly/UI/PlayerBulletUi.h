#ifndef PLAYERBULLETUI_H_
#define PLAYERBULLETUI_H_

#include "UiBase.h"

class PlayerBulletUi :public UiBase
{
public:
	PlayerBulletUi();
	~PlayerBulletUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	int m_notes_box[3];
	int m_draw_texid1, m_draw_texid2, m_draw_texid3;

	const float PLAYERBULLET_UI_POS_X = 20.0f;
	const float PLAYERBULLET_UI_POS_Y = 20.0f;


};

#endif

