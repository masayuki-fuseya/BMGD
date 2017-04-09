// ヘッダファイルの読み込み ================================================
#include "GamePlay.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
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

	m_texture_no = 0;
	m_frame_cnt = 0;
	m_music_no = 0;
	pos_y = 200.0f;
	m_is_beat = false;

	importData("test.csv");

	for (int i = 0; i < MAX_MUSIC; i++)
	{
		m_walnut[i] = nullptr;
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
	for (int i = 0; i < MAX_MUSIC; i++)
	{
		if (m_walnut[i])
		{
			delete m_walnut[i];
			m_walnut[i] = nullptr;
		}
	}
}

void GamePlay::importData(std::string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	// 読めないとき
	if (!ifs)
	{
		for (i = 0; i < MAX_MUSIC; i++)
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
	if(g_keyTracker->pressed.Z)
	{
		m_is_beat = true;
	}
	if(g_keyTracker->pressed.Space)
	{
		m_is_beat = true;
	}

	for (int i = 0; i < MAX_MUSIC; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Update();
		}
	}

	m_frame_cnt++;
	// ゴリラが手を叩く
	if (m_frame_cnt % 3 == 0)
	{
		if (m_is_beat)
		{
			m_texture_no = (m_texture_no + 1) % 5;
			if (m_texture_no == 0)
			{
				m_is_beat = false;
			}
		}
	}

	if (m_frame_cnt % 20 == 0)
	{
		// クルミを出す
		if (m_music[m_music_no] != 0)
		{
			m_walnut[m_music_no] = new Walnut(m_music[m_music_no]);
		}
		m_music_no++;
	}

	if (m_music_no == MAX_MUSIC)
	{
		*next_scene = GameMain::SELECT;
	}

	//if ()
	//{
	//	delete m_walnut[m_music_no];
	//	m_walnut[m_music_no] = nullptr;
	//}
}

void GamePlay::Render()
{
	int texture_no;
	// 何番目のゴリラを表示するか
	// 0→1→2→1→0の順番
	texture_no = abs(m_texture_no % 3 - m_texture_no / 3);

	g_spriteBatch->Draw(m_texture[texture_no]->m_pTexture, Vector2(200.0f, pos_y));

	for (int i = 0; i < MAX_MUSIC; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Render();
		}
	}
}