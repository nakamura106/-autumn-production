#ifndef SLEEPGAUGEUI_H_
#define SLEEPGAUGEUI_H_

#include "UiBase.h"

class SleepGaugeUi :public UiBase
{
public:
	SleepGaugeUi();
	~SleepGaugeUi();

	void Init()override;
	void Update()override;

private:

};

#endif

