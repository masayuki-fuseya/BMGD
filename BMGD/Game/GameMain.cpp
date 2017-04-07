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
#include "GameLogo.h"
#include "GameTitle.h"
#include "GameSelect.h"
#include "GamePlay.h"
#include "GameClear.h"
#include "GameOver.h"

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