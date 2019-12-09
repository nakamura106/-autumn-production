#ifndef FATIGUEGAUGEUI_H_
#define FATIGUEGAUGEUI_H_

#include "UiBase.h"

class FatigueGaugeUi :public UiBase
{
public:
	FatigueGaugeUi();
	~FatigueGaugeUi();

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};

#endif

