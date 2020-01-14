#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

#include "../Object/Definition.h"
#include "../Object/ObjectBase.h"
#include "../Texture/Texture.h"

// �G�t�F�N�g�̏��
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
	// EffectBase();
	EffectBase(ObjectBase* parent_);
	virtual ~EffectBase();

	virtual void Init();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �ǂ̃G�t�F�N�g���g���̂��擾����̂Ɏg��
	virtual EffectID GetEffectID() = 0;

	void WakeUp();

	void Sleep();

protected:
	bool m_IsActive = false;
	EffectParam m_param;
	ObjectBase* m_parent = nullptr;

};

#endif

