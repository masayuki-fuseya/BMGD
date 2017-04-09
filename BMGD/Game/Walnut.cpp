#include "Walnut.h"


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	クルミの種類(1:濃いクルミ　2:薄いクルミ)
//!
//!	@return		なし
//**********************************************************************
Walnut::Walnut(int kind)
{
	handle = new Texture(L"Resources\\Images\\kurumi2.png");
	grp_x = (kind - 1) * 64;
	grp_y = 0;
	grp_w = 64;
	grp_h = 64;
	pos_x = 660.0f;
	pos_y = 200.0f;
	spd_x = -5.0f;
	spd_y = 0.0f;
}


Walnut::~Walnut()
{
}