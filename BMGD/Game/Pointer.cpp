#include "Pointer.h"



Pointer::Pointer()
{
	handle = new Texture(L"Resources\\Images\\pointer.png");
	grp_x = 0;
	grp_y = 0;
	grp_w = 128;
	grp_h = 128;
	pos_x = 64.0f;
	pos_y = 106.0f;
	spd_x = 0.0f;
	spd_y = 0.0f;
}


Pointer::~Pointer()
{
}
