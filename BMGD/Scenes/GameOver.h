// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"

class GameOver :public GameBase
{
public:
	GameOver();
	~GameOver();
	void Update(int* next_scene);
	void Render();
};