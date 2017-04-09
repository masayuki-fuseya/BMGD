// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"
#include "..\Game\Walnut.h"
#include <string>

class GamePlay :public GameBase
{
private:
	Texture* m_texture[3];
	Walnut* m_walnut[128];
	int m_no;
	int m_frame_cnt;
	int m_music[128];	// 譜面
	int m_music_no;
	float pos_y;
	bool m_a_and_s;
public:
	GamePlay();
	~GamePlay();
	void importData(std::string filename);
	void Update(int* next_scene);
	void Render();
};