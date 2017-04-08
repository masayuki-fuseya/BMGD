// ヘッダファイルの読み込み ================================================
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

	m_no = 0;
	m_frame_cnt = 0;
	m_music_no = 0;
	pos_y = 200.0f;
	m_a_and_s = true;

	importData("test.csv");

	for (int i = 0; i < 128; i++)
	{
		m_walnut[i] = nullptr;
	}
}

GamePlay::~GamePlay()
{
}

void GamePlay::importData(std::string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	// 読めないとき
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
	if (g_key.Z)
	{

	}
	if (g_key.Space)
	{

	}

	for (int i = 0; i < 128; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Update();
		}
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
		if (m_music[m_music_no] != 0)
		{
			m_walnut[m_music_no] = new Walnut;
		}
		m_music_no++;
	}
}

void GamePlay::Render()
{
	g_spriteBatch->Draw(m_texture[m_no]->m_pTexture, Vector2(200.0f, pos_y));

	for (int i = 0; i < 128; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Render();
		}
	}
}