#ifndef FATIGUEGAUGEUI_H_
#define FATIGUEGAUGEUI_H_

#include "UiBase.h"
#include "../Engine/Slider.h"


class FatigueGaugeUi :public UiBase
{
public:
	FatigueGaugeUi();
	~FatigueGaugeUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Slider sliders;
	float m_fatigue_gauge;

	const float FATIGUE_GAUGE_POS_X = 1050.0f;
	const float FATIGUE_GAUGE_POS_Y = 30.0f;
};

#endif

