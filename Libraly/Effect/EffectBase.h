#ifndef EFFECTBASE_H_
#define EFFECTBASE_H_

#include "../Object/Definition.h"
#include "../Object/ObjectBase.h"
#include "../Texture/Texture.h"

// �G�t�F�N�g�̏��
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

	// �ǂ̃G�t�F�N�g���g���̂��擾����̂Ɏg��
	int GetEffectID();

	// �G�t�F�N�g�N���֐�
	void WakeUp();
	// �G�t�F�N�g�I���֐�
	void Sleep();

protected:
	EffectParam m_param;
	EffectID m_id;

};

#endif

