// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"

class GameClear :public GameBase
{
private:
	Texture* m_texture;

public:
	GameClear();
	~GameClear();
	void Update(int* next_scene);
	void Render();
};