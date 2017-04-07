// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"

class GameTitle :public GameBase
{
public:
	GameTitle();
	~GameTitle();
	void Update(int* next_scene);
	void Render();
};