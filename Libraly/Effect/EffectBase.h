#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// どのエフェクトを使うのか取得するのに使う
	int GetEffectID();

	// エフェクト起動関数
	void WakeUp();
	// エフェクト終了関数
	void Sleep();

private:


};

#endif

