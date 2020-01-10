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

	// �ǂ̃G�t�F�N�g���g���̂��擾����̂Ɏg��
	int GetEffectID();

	// �G�t�F�N�g�N���֐�
	void WakeUp();
	// �G�t�F�N�g�I���֐�
	void Sleep();

private:


};

#endif

