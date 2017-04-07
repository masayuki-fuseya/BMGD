//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2016/12/02		
//!
//! @author 	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#define _GAMEMAIN_
#include "GameMain.h"

#include "..\Scenes\GameLogo.h"
#include "..\Scenes\GameTitle.h"
#include "..\Scenes\GameSelect.h"
#include "..\Scenes\GamePlay.h"
#include "..\Scenes\GameClear.h"
#include "..\Scenes\GameOver.h"

// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
GameMain::GameMain()
{
	m_base = new GamePlay;
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::UpdateGame()
{
	//シーン管理
	if (m_next_scene != m_scene)
	{
		m_scene = m_next_scene;
		// シーン削除
		delete m_base;

		//シーンごとの呼び出し
		switch (m_scene)
		{
		case LOGO:
			m_base = new GameLogo();
			break;

		case TITLE:
			m_base = new GameTitle();
			break;

		case SELECT:
			m_base = new GameSelect();
			break;

		case PLAY:
			m_base = new GamePlay();
			break;

		case CLEAR:
			m_base = new GameClear();
			break;

		case OVER:
			m_base = new GameOver();
			break;
		}
	}
	m_base->Update();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void GameMain::RenderGame()
{
	m_base->Render();
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
GameMain::~GameMain()
{
	if (m_base)
	{
		delete m_base;
		m_base = nullptr;
	}
}