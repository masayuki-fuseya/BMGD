// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"
#include "..\Game\Walnut.h"
#include <string>

const int MAX_MUSIC = 128;

class GamePlay :public GameBase
{
private:
	Texture* m_texture[3];
	Walnut* m_walnut[MAX_MUSIC];
	int m_texture_no;
	int m_frame_cnt;
	int m_music[MAX_MUSIC];	// 譜面
	int m_music_no;
	float pos_y;
	bool m_is_beat;		// 叩くかどうかのフラグ
public:
	GamePlay();
	~GamePlay();
	void importData(std::string filename);
	void Update(int* next_scene);
	void Render();
};