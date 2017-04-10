// ヘッダファイルの読み込み ================================================
#include "GameTitle.h"
#include "..\DirectXTK.h"
#include "..\Game\GameMain.h"
#include <SimpleMath.h>


using namespace DirectX::SimpleMath;

GameTitle::GameTitle()
{
	m_texture = new Texture(L"Resources\\Images\\title.png");
}

GameTitle::~GameTitle()
{
}

void GameTitle::Update(int* next_scene)
{
	if (g_keyTracker->pressed.Enter)
	{
		*next_scene = GameMain::SELECT;
	}
}

void GameTitle::Render()
{
	g_spriteBatch->Draw(m_texture->m_pTexture, Vector2(0.0f, 0.0f));
}