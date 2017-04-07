// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"

class GameSelect :public GameBase
{
private:
	Texture* m_texture[1];
public:
	GameSelect();
	~GameSelect();
	void Update(int* next_scene);
	void Render();
};

