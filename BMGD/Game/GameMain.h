//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2016/12/02
//!
//! @author M.Fuseya
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once

#ifndef _GAMEMAIN_
#define EXTERN extern
#else
#define EXTERN
#endif

#include <windows.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include "..\DirectXTK.h"
#include "..\Texture.h"

// 定数の定義 ==============================================================

// ゲームタイトル
#define GAME_TITLE "thousand"

// ゲーム画面
#define SCREEN_WIDTH  640    // 幅[pixel]
#define SCREEN_HEIGHT 480    // 高さ[pixel]


//　構造体宣言
typedef struct tag_object
{
	Texture *handle;	//グラフィックハンドル 
	int grp_x;			//元画像のｘ座標 
	int grp_y;			//元画像のｙ座標 
	int grp_w;			//元画像の幅 
	int grp_h;			//元画像の高さ 
	float pos_x;		//座標x 
	float pos_y;		//座標y 
	float spd_x;		//速度x 
	float spd_y;		//速度y 
	int state;			//状態
	bool reversal;		//左右反転
}OBJECT;				//オブジェクト用

//　列挙型宣言
enum SCENE
{
	LOGO,
	TITLE,
	SELECT,
	PLAY,
	CLEAR,
	OVER
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);


// グローバル変数の定義 ====================================================

EXTERN int g_key_code;						//キー情報
EXTERN int g_key_old;						//前フレームのキー情報

EXTERN int g_scene;							//シーン管理
EXTERN int g_NextScene;						//次のシーン
EXTERN int g_init;							//初期化管理