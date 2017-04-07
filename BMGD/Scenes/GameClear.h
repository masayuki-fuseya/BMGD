// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GameClear :public GameBase
{
public:
	GameClear();
	~GameClear();
	void Update(int* next_scene);
	void Render();
};