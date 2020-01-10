#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

#include "../Object/Definition.h"
#include "../Object/ObjectBase.h"
#include "../Texture/Texture.h"

// エフェクトの情報
struct EffectParam
{
	float m_X, m_Y;
	float m_offsetX, m_offsetY;
	bool IsLoop;
	GameCategoryTextureList m_tex_id;
};

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

protected:
	EffectParam m_param;
	EffectID m_id;

};

#endif

