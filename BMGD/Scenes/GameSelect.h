// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"

class GameSelect :public GameBase
{
private:
	Texture* m_texture[1];
	int m_selection;
public:
	GameSelect();
	~GameSelect();
	void Update(int* next_scene);
	void Render();
};

