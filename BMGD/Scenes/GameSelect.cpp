// ヘッダファイルの読み込み ================================================
#include "GameSelect.h"
#include "..\DirectXTK.h"
#include <SimpleMath.h>
#include "..\Scenes\GamePlay.h"


using namespace DirectX::SimpleMath;


GameSelect::GameSelect()
{
	m_texture[0] = new Texture(L"Resources\\Images\\easy.png");
}

GameSelect::~GameSelect()
{
}

void GameSelect::Update(int* next_scene)
{
}

void GameSelect::Render()
{
	g_spriteBatch->Draw(m_texture[0]->m_pTexture, Vector2(200.0f, 200.0f));
}