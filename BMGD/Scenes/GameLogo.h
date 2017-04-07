// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GameLogo :public GameBase
{
public:
	GameLogo();
	~GameLogo();
	void Update();
	void Render();
};