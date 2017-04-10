// ���d�C���N���[�h�̖h�~ ==================================================
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
	Walnut** m_walnut;
	Pointer* m_pointer;
	Gorilla* m_gorilla;

	int m_no;
	int m_frame_cnt;
	int m_gorilla_cnt;				//�S�����A�j���[�V�����J�E���^
	int m_walnut_cnt;				//�N���~�J�E���^
	int* m_music;				// ����
	int m_music_no;
	int m_max_music;
	int m_selection;
	float pos_y;
	bool m_a_and_s;

	//Walnut* m_walnut;
	//bool m_is_beat;		// �@�����ǂ����̃t���O
public:
	GamePlay();
	~GamePlay();
	void importData(std::string filename);
	void Update(int* next_scene);
	void Render();
};