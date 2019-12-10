#ifndef SLEEPGAUGEUI_H_
#define SLEEPGAUGEUI_H_

#include "UiBase.h"
#include "../Engine/Slider.h"

class SleepGaugeUi :public UiBase
{
public:
	SleepGaugeUi();
	~SleepGaugeUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Slider sliders;
	float m_sleep_gauge;

};

#endif

