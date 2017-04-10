// 多重インクルードの防止 ==================================================
#pragma once

#include "GameBase.h"
#include "..\Texture.h"
#include "..\Game\Walnut.h"
#include "..\Game\Pointer.h"
#include "..\Game\Gorilla.h"
#include <string>

const int MAX_MUSIC = 128;

class GamePlay :public GameBase
{
private:
	Texture* m_texture[3];
	Walnut* m_walnut[MAX_MUSIC];
	Pointer* m_pointer;
	Gorilla* m_gorilla;

	int m_no;
	int m_frame_cnt;
	int m_gorilla_cnt;				//ゴリラアニメーションカウンタ
	int m_walnut_cnt;				//クルミカウンタ
	int m_music[MAX_MUSIC];				// 譜面
	int m_music_no;
	float pos_y;
	bool m_a_and_s;

	//Walnut* m_walnut;
	//bool m_is_beat;		// 叩くかどうかのフラグ
public:
	GamePlay();
	~GamePlay();
	void importData(std::string filename);
	void Update(int* next_scene);
	void Render();
};