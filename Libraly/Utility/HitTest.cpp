#include "HitTest.h"
#include "../Object/Definition.h"
#include <math.h>


bool IsHitTest(ObjectBase *obj1,ObjectBase *obj2)
{
	SaveRectangle rect1, rect2;
	rect1.x = obj1->GetPos().x;
	rect1.y = obj1->GetPos().y;
	rect1.width = obj1->GetRectParam().width;
	rect1.height = obj1->GetRectParam().height;
	rect1.shift_x = obj1->GetRectParam().shift_x;
	rect1.shift_y = obj1->GetRectParam().shift_y;
	rect2.x = obj2->GetPos().x;
	rect2.y = obj2->GetPos().y;
	rect2.width = obj2->GetRectParam().width;
	rect2.height = obj2->GetRectParam().height;
	rect2.shift_x = obj2->GetRectParam().shift_x;
	rect2.shift_y = obj2->GetRectParam().shift_y;

	rect1.x += rect1.shift_x + (rect1.width / 2.0f);
	rect1.y += rect1.shift_y + (rect1.height / 2.0f);
	rect2.x += rect2.shift_x + (rect2.width / 2.0f);
	rect2.y += rect2.shift_y + (rect2.height / 2.0f);


	if (rect1.x - rect2.x <= fabsf((rect1.width / 2.0f) + (rect2.width / 2.0f))
		&& rect1.y - rect2.y <= fabsf((rect1.height / 2.0f) + (rect2.height / 2.0f)))
	{
		return true;
	}

	return false;
}

