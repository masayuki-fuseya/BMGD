// ヘッダファイルの読み込み ================================================
#include "GamePlay.h"
#include "..\DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

GamePlay::GamePlay()
{
	m_texture[0] = new Texture(L"Resources\\Images\\gorira1.png");
	m_texture[1] = new Texture(L"Resources\\Images\\gorira2.png");
	m_texture[2] = new Texture(L"Resources\\Images\\gorira3.png");

	m_no = 0;
	m_frame_cnt = 0;
	pos_y = 200.0f;
	m_a_and_s = true;
}

GamePlay::~GamePlay()
{
}

void GamePlay::Update(int* next_scene)
{
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
}

void GamePlay::Render()
{
	g_spriteBatch->Draw(m_texture[m_no]->m_pTexture, Vector2(200.0f, pos_y));
}