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
};

#endif

