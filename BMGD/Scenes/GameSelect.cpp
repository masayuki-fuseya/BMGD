// ヘッダファイルの読み込み ================================================
#include "GameSelect.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;


GameSelect::GameSelect()
{
	m_selection = 0;
	m_texture[0] = new Texture(L"Resources\\Images\\dededon.png");
	m_texture[1] = new Texture(L"Resources\\Images\\dededon2.png");
	m_texture[2] = new Texture(L"Resources\\Images\\japa.png");
}

GameSelect::~GameSelect()
{
	if (m_texture[0])
	{
		delete m_texture[0];
		m_texture[0] = nullptr;
	}
}


void GameSelect::Update(int* next_scene)
{
	if (g_keyTracker->pressed.Up)
	{
		m_selection = (m_selection + 2) % 3;
	}
	if (g_keyTracker->pressed.Down)
	{
		m_selection = (m_selection + 1) % 3;
	}
	if (g_keyTracker->pressed.Enter)
	{
		*next_scene = GameMain::PLAY;
	}
	
}

void GameSelect::Render()
{
	g_spriteBatch->Draw(m_texture[m_selection]->m_pTexture, Vector2(0.0f, 0.0f));
}