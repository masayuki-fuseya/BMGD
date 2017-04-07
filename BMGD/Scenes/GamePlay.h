// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"

class GamePlay :public GameBase
{
private:
	Texture* m_texture[3];
	int m_no;
	int m_frame_cnt;
	float pos_y;
	bool m_a_and_s;
public:
	GamePlay();
	~GamePlay();
	void Update(int* next_scene);
	void Render();
};