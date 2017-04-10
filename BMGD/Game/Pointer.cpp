#include "Pointer.h"



Pointer::Pointer()
{
	handle = new Texture(L"Resources\\Images\\lane.png");
	grp_x = 0;
	grp_y = 0;
	grp_w = 600;
	grp_h = 188;
	pos_x = 50.0f;
	pos_y = 80.0f;
	spd_x = 0.0f;
	spd_y = 0.0f;
}


Pointer::~Pointer()
{
}
