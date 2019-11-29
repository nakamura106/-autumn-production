#ifndef BULLETBASE_H_
#define BULLETBASE_H_

#include "../Object/ObjectBase.h"

class BulletBase :public ObjectBase
{
public:
	BulletBase();
	~BulletBase();
	virtual void Init();
	virtual void Update();
	virtual void Load();
	void Create() {}

private:

protected:


};


#endif
