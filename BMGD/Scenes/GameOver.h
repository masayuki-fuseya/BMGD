// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GameOver :public GameBase
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render();
};