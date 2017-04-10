// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GamePlay.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
#include <SimpleMath.h>
#include <fstream>
#include <istream>
#include <sstream>

#include "..\ADX2Le.h"
#include "..\Game\CueSheet_0.h"

using namespace std;
using namespace DirectX::SimpleMath;

GamePlay::GamePlay()
{
	m_texture[0] = new Texture(L"Resources\\Images\\gorira1.png");
	m_texture[1] = new Texture(L"Resources\\Images\\gorira2.png");
	m_texture[2] = new Texture(L"Resources\\Images\\gorira3.png");

	m_pointer = new Pointer();
	m_gorilla = new Gorilla();
	

	m_no = 0;
	m_frame_cnt = 0;
	m_gorilla_cnt = 0;
	m_walnut_cnt = 0;
	m_music_no = 0;
	pos_y = 200.0f;
	m_max_music = 0;

	m_selection = 2;

	switch (m_selection)
	{
		case 0:
			importData("dededon.csv");
			break;

		case 1:
			importData("Hallelujah.csv");
			break;

		case 2:
			importData("japaripark.csv");
			break;
	}
	
	
	m_walnut = new Walnut*[m_max_music];
	for (int i = 0; i < m_max_music; i++)
	{
		m_walnut[i] = new Walnut();
	}

	
}

GamePlay::~GamePlay()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_texture[i])
		{
			delete m_texture[i];
			m_texture[i] = nullptr;
		}
	}
	for (int i = 0; i < m_max_music; i++)
	{
		if (m_walnut[i])
		{
			delete m_walnut[i];
			m_walnut[i] = nullptr;
		}
	}
	if (m_pointer)
	{
		delete m_pointer;
		m_pointer = nullptr;
	}
	if (m_gorilla)
	{
		delete m_gorilla;
		m_gorilla = nullptr;
	}
}

void GamePlay::importData(std::string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	// �ǂ߂Ȃ��Ƃ�
	if (!ifs)
	{
		return;
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		while (getline(stream, token, ','))
		{
			if (i == 0)
			{
				m_max_music = atoi(token.c_str());
				m_music = new int[m_max_music];
			}
			
			m_music[i] = atoi(token.c_str());
			i++;

		/*	if (m_music[i] == 3)
			{
				break;
			}*/
		}
	}
}

void GamePlay::Update(int* next_scene)
{
	if (g_keyTracker->pressed.Z)
	{
		ADX2Le::Play(DON);
	}

	if (g_keyTracker->pressed.Space)
	{
		ADX2Le::Play(KA);
	}

	if ((g_keyTracker->pressed.Z)|| (g_keyTracker->pressed.Space))
	{
		//�S������State���P�ɕύX����
		m_gorilla->SetState(1);

		for (int i = m_walnut_cnt; i < m_max_music; i++)
		{
			//�N���~��pointer�̘g�̒��ɂ���ꍇ
			if ((m_walnut[i]->GetPosX() < m_pointer->GetPosX() + 128) &&
				(m_walnut[i]->GetPosX() + m_walnut[i]->GetGrpW() > m_pointer->GetPosX()))
			{
				if ((g_keyTracker->pressed.Z) && (m_walnut[i]->GetState() == 1))
				{
					m_walnut[i]->SetState(0);
					
				}
				if ((g_keyTracker->pressed.Space) && (m_walnut[i]->GetState() == 2))
				{
					m_walnut[i]->SetState(0);
				
				}
			}
		}
	}
	
	

	for (int i = m_walnut_cnt; i < m_max_music; i++)
	{
		if (m_walnut[i]->GetPosX() + m_walnut[i]->GetGrpW() < -64)
		{
			m_walnut_cnt++;
		}
	}

	
	if (m_frame_cnt == 0)
	{
		switch (m_selection)
		{
			case 0:
				ADX2Le::Play(DEDEDON);
				break;

			case 1:
				ADX2Le::Play(SERORI);
				break;

			case 2:
				ADX2Le::Play(JAPARIPARK);
				break;
		}
		
	}
	m_frame_cnt++;

	if (m_frame_cnt % 11 == 0)//�R�C�c
	{
		if (!(m_music_no == m_max_music))
		{
			// �N���~���o��
			if (m_music[m_music_no] == 1)
			{
				m_walnut[m_music_no]->SetState(1);
			}
		
			if (m_music[m_music_no] == 2)
			{
				m_walnut[m_music_no]->SetState(2);
			}

			m_walnut[m_music_no]->SetGrpX(m_walnut[m_music_no]->GetGrpW() * (m_music[m_music_no] - 1));
			m_music_no++;
		}
	}

	if (m_frame_cnt % 2 == 0)
	{
		//�S�����̃A�j���[�V����
		if (m_gorilla->GetState() == 1)
		{
			m_gorilla_cnt = (m_gorilla_cnt + 1) % 4;
			int gorilla_cnt;
			// ���Ԗڂ̃S������\�����邩
			// 0��1��2��1��0�̏���
			gorilla_cnt = abs(m_gorilla_cnt % 3 - m_gorilla_cnt / 3);

			m_gorilla->SetGrpX(m_gorilla->GetGrpW() * gorilla_cnt);

			if (gorilla_cnt == 0)
			{
				m_gorilla->SetState(0);
			}
		}
	}

//	for (int i = m_walnut_cnt; m_walnut[i] != nullptr; i++)
	for (int i = m_walnut_cnt; i < m_max_music; i++)
	{
		if (m_walnut[i]->GetState() != 0)
		{
			m_walnut[i]->Update();
		}
	}

	if (m_music_no == m_max_music)
	{
		*next_scene = GameMain::CLEAR;
	}

	
}

void GamePlay::Render()
{
	//m_pointer�̕`��
	m_pointer->Render();

	for (int i = m_walnut_cnt; i<m_max_music; i++)
	{
		if (m_walnut[i]->GetState() != 0)
		{
			m_walnut[i]->Render();
		}
	}

	//m_gorilla�̕`��
	m_gorilla->Render();
}