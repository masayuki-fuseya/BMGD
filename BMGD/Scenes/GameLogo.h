// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"

class GameLogo :public GameBase
{
public:
	GameLogo();
	~GameLogo();
	void Update(int* next_scene);
	void Render();
};