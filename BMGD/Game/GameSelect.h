// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GameSelect :public GameBase
{
public:
	GameSelect();
	~GameSelect();
	void Update();
	void Render();
};

