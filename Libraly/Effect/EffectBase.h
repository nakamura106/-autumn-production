#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

#include "../Object/Definition.h"
#include "../Object/ObjectBase.h"
#include "../Texture/Texture.h"

// エフェクトの情報
struct EffectParam
{
	EffectParam()
	{
		m_X = 0.f;
		m_Y = 0.f;
		m_offsetX = 0.f;
		m_offsetY = 0.f;
		IsLoop = false;
		m_tex_id = GameCategoryTextureList::GameTextureNone;
	}

	float m_X, m_Y;
	float m_offsetX, m_offsetY;
	bool IsLoop;
	GameCategoryTextureList m_tex_id;
};

class EffectBase
{
public:
	EffectBase();
	EffectBase(ObjectBase* parent_);
	virtual ~EffectBase();

	virtual void Init();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// どのエフェクトを使うのか取得するのに使う
	virtual EffectID GetEffectID() = 0;

	// エフェクト起動関数
	void WakeUp();
	// エフェクト終了関数
	void Sleep();

protected:
	EffectParam m_param;
	ObjectBase* m_parent = nullptr;

};

#endif

