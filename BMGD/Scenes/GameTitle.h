// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"

class GameTitle :public GameBase
{
private:
	Texture* m_texture;

public:
	GameTitle();
	~GameTitle();
	void Update(int* next_scene);
	void Render();
};