// ヘッダファイルの読み込み ================================================
#include "GameClear.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
#include <SimpleMath.h>


using namespace DirectX::SimpleMath;

GameClear::GameClear()
{
	m_texture = new Texture(L"Resources\\Images\\clear.png");
}

GameClear::~GameClear()
{
}

void GameClear::Update(int* next_scene)
{
	if (g_keyTracker->pressed.Enter)
	{
		*next_scene = GameMain::SELECT;
	}
}

void GameClear::Render()
{
	g_spriteBatch->Draw(m_texture->m_pTexture, Vector2(0.0f, 0.0f));
}
