//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2016/12/02		
//!
//! @author M.Fuseya	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#define _GAMEMAIN_
#include "GameMain.h"

#include "..\Scenes\GameBase.h"
#include "..\Scenes\GameLogo.h"
#include "..\Scenes\GameTitle.h"
#include "..\Scenes\GameSelect.h"
#include "..\Scenes\GamePlay.h"
#include "..\Scenes\GameClear.h"
#include "..\Scenes\GameOver.h"

// プロトタイプ宣言 ====================================================


// グローバル変数の定義 ====================================================
GameBase* base;

// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//シーン管理
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		// シーン削除
		delete base;
		g_init = 0;

		//シーンごとの呼び出し
		switch (g_scene)
		{
		case LOGO:
			base = new GameLogo();
			break;

		case TITLE:
			base = new GameTitle();
			break;

		case SELECT:
			base = new GameSelect();
			break;

		case PLAY:
			base = new GamePlay();
			break;

		case CLEAR:
			base = new GameClear();
			break;

		case OVER:
			base = new GameOver();
			break;
		}
	}
	base->Update();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
	base->Render();
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
}