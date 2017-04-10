// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GamePlay.h"
#include "..\DirectXTK.h"
#include <SimpleMath.h>
#include <fstream>
#include <istream>
#include <sstream>

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
	m_a_and_s = true;

	importData("test.csv");

	m_walnut = new Walnut*[128];

	for (int i = 0; i < 128; i++)
	{
		m_walnut[i] = nullptr;
		m_walnut[i] = new Walnut();
	}
}

GamePlay::~GamePlay()
{
	delete m_pointer;
	delete m_gorilla;
}

void GamePlay::importData(std::string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	// �ǂ߂Ȃ��Ƃ�
	if (!ifs)
	{
		for (i = 0; i < 128; i++)
		{
			m_music[i] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		while (getline(stream, token, ','))
		{
			m_music[i] = atoi(token.c_str());
			i++;
		}
	}
}

void GamePlay::Update(int* next_scene)
{
	if (g_keyTracker->pressed.Z)
	{
		//�S������State���P�ɕύX����
		m_gorilla->SetState(1);

		//�N���~��pointer�̘g�̒��ɂ���ꍇ
		if (m_walnut[m_walnut_cnt]->GetPosX() + m_walnut[m_walnut_cnt]->GetGrpW() < m_pointer->GetPosX() + m_pointer->GetGrpW())
		{
			delete m_walnut[m_walnut_cnt];
			m_walnut_cnt++;
		}
	}

	if (g_key.Space)
	{

	}

	m_frame_cnt++;
	if (m_frame_cnt % 6 == 0)
	{
		if (m_a_and_s)
		{
			m_no = (m_no + 1) % 3;
			pos_y -= 50.0f;
			if (m_no == 2)
			{
				m_a_and_s = !m_a_and_s;
			}
		}
		else
		{
			m_no = (m_no + 2) % 3;
			pos_y += 50.0f;
			if (m_no == 0)
			{
				m_a_and_s = !m_a_and_s;
			}
		}
	}

	if (m_frame_cnt % 30 == 0)
	{
		if (m_music[m_music_no] != 2)
		{
			m_walnut[m_music_no] = new Walnut;
		//	m_walnut[m_music_no] = new Walnut();
			m_walnut[m_music_no]->SetState(1);
			m_walnut[m_music_no]->SetGrpX(m_walnut[m_music_no]->GetGrpW() * m_music[m_music_no] );
		}
		m_music_no++;
	}

	//�S�����̃A�j���[�V����
	if (m_gorilla->GetState() == 1)
	{
		if (m_frame_cnt % 6 == 0)
		{
			m_gorilla_cnt++;
			m_gorilla->SetGrpX(m_gorilla->GetGrpW() * m_gorilla_cnt);
		}

		//�@���I����Ă����珉����Ԃɖ߂�
		if (m_gorilla_cnt >= 3)
		{
			m_gorilla_cnt = 0;
			m_gorilla->SetGrpX(0);
			m_gorilla->SetState(0);
		}
	}

	//�X�V����
	for (int i = m_walnut_cnt; i < 128; i++)
	{
		if (m_walnut[i]->GetState() != 0)
		{
			m_walnut[i]->Update();
		}
	}
}

void GamePlay::Render()
{
	//m_pointer�̕`��
	m_pointer->Render();

	g_spriteBatch->Draw(m_texture[m_no]->m_pTexture, Vector2(200.0f, pos_y));

	for (int i = m_walnut_cnt; i < 128; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Render();
		}
	}

	//m_gorilla�̕`��
	m_gorilla->Render();
}