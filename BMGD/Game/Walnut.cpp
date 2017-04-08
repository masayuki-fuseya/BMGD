#include "Walnut.h"



Walnut::Walnut()
{
	handle = new Texture(L"Resources\\Images\\kurumi2.png");
	grp_x = 0;
	grp_y = 0;
	grp_w = 64;
	grp_h = 64;
	pos_x = 660.0f;
	pos_y = 200.0f;
	spd_x = -3.0f;
	spd_y = 0.0f;
}


Walnut::~Walnut()
{
}