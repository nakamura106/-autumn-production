#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

#include "../Object/ObjectBase.h"
#include "../Object/Definition.h"
#include "../Texture/Texture.h"

class ObjectBase;

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
	}

	float m_X, m_Y;
	float m_offsetX, m_offsetY;
	bool IsLoop;
};

class EffectBase
{
public:
	// EffectBase();
	EffectBase(ObjectBase* parent_);
	virtual ~EffectBase();

	virtual void Init();
	virtual void Update();
	void Draw();

	// �ǂ̃G�t�F�N�g���g���̂��擾����̂Ɏg��
	virtual EffectID GetEffectID() = 0;

	bool GetIsActive()
	{
		return m_IsActive;
	}

	// �N���֐�
	void WakeUp();
	// �I���֐�
	void Sleep();

	// �A�j���[�V�����ɕK�v�Ȋ֐�
	void AnimationUpdate();
	int GetAnimationTexNum();

	bool GetIsAnimeEnd() { return m_is_animation_end; }


protected:
	bool m_IsActive = false;
	EffectParam m_effect_param;
	DrawParam m_draw_param;
	AnimationParam m_anime_param;
	ObjectBase* m_parent = nullptr;

	// �A�j���[�V�����p�����o�ϐ�
	int m_animation_timer;
	bool m_is_animation_end;

};

#endif

