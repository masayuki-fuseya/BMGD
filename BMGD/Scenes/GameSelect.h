// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"

class GameSelect :public GameBase
{
public:
	GameSelect();
	~GameSelect();
	void Update(int* next_scene);
	void Render();
};

