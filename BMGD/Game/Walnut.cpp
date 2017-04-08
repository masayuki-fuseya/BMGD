#include "Walnut.h"



Walnut::Walnut()
{
	handle = new Texture(L"Resources\\Images\\ball.png");
	grp_x = 0;
	grp_y = 0;
	grp_w = 32;
	grp_h = 32;
	pos_x = 660.0f;
	pos_y = 200.0f;
	spd_x = -3.0f;
	spd_y = 0.0f;
}


Walnut::~Walnut()
{
}