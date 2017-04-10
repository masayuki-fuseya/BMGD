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

	m_pointer = new Pointer();
	m_gorilla = new Gorilla();

	m_no = 0;
	m_frame_cnt = 0;
	m_gorilla_cnt = 0;
	m_walnut_cnt = 0;
	m_music_no = 0;
	pos_y = 200.0f;
	//m_is_beat = false;

	importData("test.csv");

	//m_walnut = new Walnut*[MAX_MUSIC];

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
	if (g_keyTracker->pressed.Z)
	{
		//ゴリラのStateを１に変更する
		m_gorilla->SetState(1);

		if (m_walnut[m_walnut_cnt])
		{
			//クルミがpointerの枠の中にある場合
			if (m_walnut[m_walnut_cnt]->GetPosX() + m_walnut[m_walnut_cnt]->GetGrpW() < m_pointer->GetPosX() + m_pointer->GetGrpW())
			{
				delete m_walnut[m_walnut_cnt];
				m_walnut[m_walnut_cnt] = nullptr;
				m_walnut_cnt++;
			}
		}
	}
	
	for (int i = m_walnut_cnt; m_walnut[i] != nullptr; i++)
	{
		if (m_walnut[i] && m_walnut[i]->GetState() != 0)
		{
			m_walnut[i]->Update();
		}
	}

	m_frame_cnt++;
	if (m_frame_cnt % 20 == 0)
	{
		// クルミを出す
		if (m_music[m_music_no] != 2)
		{
			m_walnut[m_music_no] = new Walnut;
			m_walnut[m_music_no]->SetState(1);
			m_walnut[m_music_no]->SetGrpX(m_walnut[m_music_no]->GetGrpW() * m_music[m_music_no]);
			m_music_no++;
		}
	}

	if (m_frame_cnt % 2 == 0)
	{
		//ゴリラのアニメーション
		if (m_gorilla->GetState() == 1)
		{
			m_gorilla_cnt = (m_gorilla_cnt + 1) % 5;
			int gorilla_cnt;
			// 何番目のゴリラを表示するか
			// 0→1→2→1→0の順番
			gorilla_cnt = abs(m_gorilla_cnt % 3 - m_gorilla_cnt / 3);

			m_gorilla->SetGrpX(m_gorilla->GetGrpW() * gorilla_cnt);

			if (gorilla_cnt == 0)
			{
				m_gorilla->SetState(0);
			}
		}
	}

	if (m_music_no == MAX_MUSIC)
	{
		*next_scene = GameMain::SELECT;
	}
}

void GamePlay::Render()
{
	//m_pointerの描画
	m_pointer->Render();

	for (int i = m_walnut_cnt; m_walnut[i] != nullptr; i++)
	{
		if (m_walnut[i])
		{
			m_walnut[i]->Render();
		}
	}

	//m_gorillaの描画
	m_gorilla->Render();
}