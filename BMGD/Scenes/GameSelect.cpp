// ヘッダファイルの読み込み ================================================
#include "GameSelect.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;


GameSelect::GameSelect()
	:m_selection(0)
{
	m_texture[0] = new Texture(L"Resources\\Images\\easy.png");
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
	if (g_key.Up)
	{
		m_selection = (m_selection + 2) % 3;
	}
	if (g_key.Down)
	{
		m_selection = (m_selection + 1) % 3;
	}
	if (g_key.Z)
	{
		*next_scene = GameMain::PLAY;
	}
}

void GameSelect::Render()
{
	g_spriteBatch->Draw(m_texture[0]->m_pTexture, Vector2(200.0f, 200.0f));
}