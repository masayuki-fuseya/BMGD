//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// メイン
//
// 備考：このプログラムはDirectX11を使用するための最低必要と思われる処理を組み込んだサンプルです
//       余分な処理は記述していませんのでオリジナルフレームワークのベースに使用してください
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <Windows.h>
#include <DirectXColors.h>
#include "Direct3D.h"
#include "DirectXTK.h"
#include "ImaseLib\FPSTimer.h"
#include <SimpleMath.h>
#include "Game\GameMain.h"
#include <dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;
using namespace DirectX;

//////////////////
// 定数宣言		//
//////////////////
// ウインドウスタイル
static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

// 画面解像度
static const int WINDOW_W = 640;
static const int WINDOW_H = 480;

//////////////////////////////
// 関数のプロトタイプ宣言	//
//////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool Init();
bool CreatePrimaryBuffer();
bool CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, const char* file);
bool Exit();

//////////////////////
// グローバル変数	//
//////////////////////
HINSTANCE g_hInst = nullptr;	// インスタンスハンドル
HWND g_hWnd = nullptr;	// ウインドウハンドル

LPDIRECTSOUND8 g_lpDS = nullptr;
LPDIRECTSOUNDBUFFER g_lpPrimary = nullptr;
LPDIRECTSOUNDBUFFER g_lpSecondary = nullptr;

//--------------------------------------------------------------------------------------
// メイン
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 1秒間に60フレームで固定する
	ImaseLib::FPSTimer fpsTimer(60);

	// ウインドウの作成
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	// DirectXデバイスの初期化
	if (FAILED(Direct3D_InitDevice(g_hWnd)))
	{
		// 初期化に失敗
		Direct3D_CleanupDevice();
		return 0;
	}

	// DirectXTK関係の初期化
	DirectXTK_Initialize();

	// DirectSound初期化
	if (!Init()) {
		Exit();
		return 0;
	}

	// プライマリサウンドバッファ
	if (!CreatePrimaryBuffer()) {
		Exit();
		return 0;
	}

	// サウンドバッファ						WAVEファイルを指定
	if (!CreateSoundBuffer(&g_lpSecondary, "Resources\\Sounds\\dededon.wav")) {
		Exit();
		return 0;
	}


	GameMain* main = new GameMain;		//ゲームの初期化処理


	// メインループ
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		int fps = fpsTimer.GetNowFPS();
		wchar_t buf[16];
		swprintf_s(buf, 16, L"fps = %d", fps);

		// メッセージが来ているか調べる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// メッセージが来ていればウインドウプロシージャへ送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// キー入力やマウス情報の更新
			DirectXTK_UpdateInputState();

			if (g_keyTracker->pressed.Escape)
			{
				break;
			}

			main->UpdateGame();		//ゲームの更新処理


			// バックバッファのクリア
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// 深度バッファのクリア
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			//---------- ここで描画コマンドを発行する　---------//
			g_spriteBatch->Begin(SpriteSortMode_Deferred, g_pCommonStates->NonPremultiplied(), g_pCommonStates->PointClamp());


			main->RenderGame();		//ゲームの描画処理


			// fpsの表示
			g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));

			g_spriteBatch->End();

			// 画面更新を待つ
			fpsTimer.WaitFrame();

			// バックバッファとフロントバッファを入れ替える
			g_pSwapChain->Present(0, 0);
		}
	}


	delete main;			//ゲームの後始末処理


	Exit();

	// DirectXデバイス周りの終了処理
	Direct3D_CleanupDevice();

	return 0;
}

//--------------------------------------------------------------------------------------
// ウインドウの作成
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ウインドウクラスを登録する
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)NULL);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// ウインドウを作成する
	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ←ウインドウサイズ
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	g_hWnd = CreateWindow(L"WindowClass", L"サンプルフレームワーク", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ウインドウプロシージャー
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:		// ウインドウが破棄されたメッセージ
		PostQuitMessage(0);	// WM_QUITメッセージを送出する（メインループを抜ける）
		break;

	case WM_ACTIVATEAPP:	// ウインドウがアクティブ化、非アクティブ化する時に来るメッセージ
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:		// キー入力関係のメッセージ
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:			// マウス関係のメッセージ
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	default:
		// 自分で処理しないメッセージはDefWindowProc関数に任せる
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool Init()
{
	HRESULT ret;

	// COMの初期化
	CoInitialize(nullptr);

	// DirectSound8を作成
	ret = DirectSoundCreate8(nullptr, &g_lpDS, nullptr);
	if (FAILED(ret)) {
		return false;
	}

	// 強調モード
	ret = g_lpDS->SetCooperativeLevel(g_hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(ret)) {
		return false;
	}

	return true;
}

bool CreatePrimaryBuffer()
{
	HRESULT ret;
	WAVEFORMATEX wf;

	// プライマリサウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = nullptr;
	ret = g_lpDS->CreateSoundBuffer(&dsdesc, &g_lpPrimary, nullptr);
	if (FAILED(ret)) {
		return false;
	}

	// プライマリバッファのステータスを決定
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = g_lpPrimary->SetFormat(&wf);
	if (FAILED(ret)) {
		return false;
	}

	return true;
}

bool CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, const char* file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf;

	// WAVファイルをロード
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, nullptr, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc) {
		return false;
	}

	// 'WAVE'チャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, nullptr, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		mmioClose(hSrc, 0);
		return false;
	}

	// 'fmt 'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		mmioClose(hSrc, 0);
		return false;
	}

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize<sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf) {
		mmioClose(hSrc, 0);
		return false;
	}
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVEフォーマットのロード
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}


	// fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// dataチャンクを探す
	while (true) {
		// 検索
		ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		if (FAILED(ret)) {
			free(wf);
			mmioClose(hSrc, 0);
			return false;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// 次のチャンクへ
		ret = mmioAscend(hSrc, &mSrcWaveData, 0);
	}


	// サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = g_lpDS->CreateSoundBuffer(&dsdesc, dsb, nullptr);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	// ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	// データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ロック解除
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// ヘッダ用メモリを開放
	free(wf);

	// WAVを閉じる
	mmioClose(hSrc, 0);

	return true;
}

bool Exit()
{
	if (g_lpSecondary) {
		g_lpSecondary->Release();
		g_lpSecondary = nullptr;
	}

	if (g_lpPrimary) {
		g_lpPrimary->Release();
		g_lpPrimary = nullptr;
	}

	if (g_lpDS) {
		g_lpDS->Release();
		g_lpDS = nullptr;
	}

	// COMの終了
	CoUninitialize();

	return true;
}
