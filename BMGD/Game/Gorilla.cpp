#include "Gorilla.h"



Gorilla::Gorilla()
{
	handle = new Texture(L"Resources\\Images\\gorira.png");
	grp_x = 0;
	grp_y = 0;
	grp_w = 256;
	grp_h = 256;
	pos_x = 0.0f;
	pos_y = 144.0f;
	spd_x = -3.0f;
	spd_y = 0.0f;
	state = 0;
}


Gorilla::~Gorilla()
{
}
