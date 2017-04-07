// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GamePlay :public GameBase
{
public:
	GamePlay();
	~GamePlay();
	void Update();
	void Render();
};