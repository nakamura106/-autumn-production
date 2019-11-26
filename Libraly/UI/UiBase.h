#ifndef UIBASE_H_
#define UIBASE_H_

struct UiParam
{
	UiParam() {
		x = 0;
		y = 0;
	}
	float x, y;
};

class UiBase {
public:
	UiBase();
	~UiBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	void Draw();

private:
	UiParam m_param;
};

#endif
