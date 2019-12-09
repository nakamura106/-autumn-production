#ifndef HITTEST_H_
#define HITTEST_H_

#include "../Manager/ObjectManager.h"
#include "../Object/ObjectBase.h"

struct SaveRectangle
{
	float x, y, width, height, shift_x, shift_y;
};


bool IsHitTest(ObjectBase* obj1, ObjectBase* obj2);

#endif

