// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"

class GamePlay :public GameBase
{
public:
	GamePlay();
	~GamePlay();
	void Update(int* next_scene);
	void Render();
};