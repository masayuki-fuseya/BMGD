//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// ���C��
//
// ���l�F���̃v���O������DirectX11���g�p���邽�߂̍Œ�K�v�Ǝv���鏈����g�ݍ��񂾃T���v���ł�
//       �]���ȏ����͋L�q���Ă��܂���̂ŃI���W�i���t���[�����[�N�̃x�[�X�Ɏg�p���Ă�������
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
// �萔�錾		//
//////////////////
// �E�C���h�E�X�^�C��
static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

// ��ʉ𑜓x
static const int WINDOW_W = 640;
static const int WINDOW_H = 480;

//////////////////////////////
// �֐��̃v���g�^�C�v�錾	//
//////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool Init();
bool CreatePrimaryBuffer();
bool CreateSoundBuffer(LPDIRECTSOUNDBUFFER* dsb, const char* file);
bool Exit();

//////////////////////
// �O���[�o���ϐ�	//
//////////////////////
HINSTANCE g_hInst = nullptr;	// �C���X�^���X�n���h��
HWND g_hWnd = nullptr;	// �E�C���h�E�n���h��

LPDIRECTSOUND8 g_lpDS = nullptr;
LPDIRECTSOUNDBUFFER g_lpPrimary = nullptr;
LPDIRECTSOUNDBUFFER g_lpSecondary = nullptr;

//--------------------------------------------------------------------------------------
// ���C��
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 1�b�Ԃ�60�t���[���ŌŒ肷��
	ImaseLib::FPSTimer fpsTimer(60);

	// �E�C���h�E�̍쐬
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	// DirectX�f�o�C�X�̏�����
	if (FAILED(Direct3D_InitDevice(g_hWnd)))
	{
		// �������Ɏ��s
		Direct3D_CleanupDevice();
		return 0;
	}

	// DirectXTK�֌W�̏�����
	DirectXTK_Initialize();

	// DirectSound������
	if (!Init()) {
		Exit();
		return 0;
	}

	// �v���C�}���T�E���h�o�b�t�@
	if (!CreatePrimaryBuffer()) {
		Exit();
		return 0;
	}

	// �T�E���h�o�b�t�@						WAVE�t�@�C�����w��
	if (!CreateSoundBuffer(&g_lpSecondary, "Resources\\Sounds\\dededon.wav")) {
		Exit();
		return 0;
	}


	GameMain* main = new GameMain;		//�Q�[���̏���������


	// ���C�����[�v
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		int fps = fpsTimer.GetNowFPS();
		wchar_t buf[16];
		swprintf_s(buf, 16, L"fps = %d", fps);

		// ���b�Z�[�W�����Ă��邩���ׂ�
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// ���b�Z�[�W�����Ă���΃E�C���h�E�v���V�[�W���֑���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �L�[���͂�}�E�X���̍X�V
			DirectXTK_UpdateInputState();

			if (g_keyTracker->pressed.Escape)
			{
				break;
			}

			main->UpdateGame();		//�Q�[���̍X�V����


			// �o�b�N�o�b�t�@�̃N���A
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// �[�x�o�b�t�@�̃N���A
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			//---------- �����ŕ`��R�}���h�𔭍s����@---------//
			g_spriteBatch->Begin(SpriteSortMode_Deferred, g_pCommonStates->NonPremultiplied(), g_pCommonStates->PointClamp());


			main->RenderGame();		//�Q�[���̕`�揈��


			// fps�̕\��
			g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));

			g_spriteBatch->End();

			// ��ʍX�V��҂�
			fpsTimer.WaitFrame();

			// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���
			g_pSwapChain->Present(0, 0);
		}
	}


	delete main;			//�Q�[���̌�n������


	Exit();

	// DirectX�f�o�C�X����̏I������
	Direct3D_CleanupDevice();

	return 0;
}

//--------------------------------------------------------------------------------------
// �E�C���h�E�̍쐬
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// �E�C���h�E�N���X��o�^����
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

	// �E�C���h�E���쐬����
	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ���E�C���h�E�T�C�Y
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	g_hWnd = CreateWindow(L"WindowClass", L"�T���v���t���[�����[�N", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// �E�C���h�E�v���V�[�W���[
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:		// �E�C���h�E���j�����ꂽ���b�Z�[�W
		PostQuitMessage(0);	// WM_QUIT���b�Z�[�W�𑗏o����i���C�����[�v�𔲂���j
		break;

	case WM_ACTIVATEAPP:	// �E�C���h�E���A�N�e�B�u���A��A�N�e�B�u�����鎞�ɗ��郁�b�Z�[�W
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:		// �L�[���͊֌W�̃��b�Z�[�W
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:			// �}�E�X�֌W�̃��b�Z�[�W
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
		// �����ŏ������Ȃ����b�Z�[�W��DefWindowProc�֐��ɔC����
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool Init()
{
	HRESULT ret;

	// COM�̏�����
	CoInitialize(nullptr);

	// DirectSound8���쐬
	ret = DirectSoundCreate8(nullptr, &g_lpDS, nullptr);
	if (FAILED(ret)) {
		return false;
	}

	// �������[�h
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

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
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

	// �v���C�}���o�b�t�@�̃X�e�[�^�X������
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

	// WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, nullptr, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc) {
		return false;
	}

	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, nullptr, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		mmioClose(hSrc, 0);
		return false;
	}

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		mmioClose(hSrc, 0);
		return false;
	}

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize<sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf) {
		mmioClose(hSrc, 0);
		return false;
	}
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}


	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// data�`�����N��T��
	while (true) {
		// ����
		ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		if (FAILED(ret)) {
			free(wf);
			mmioClose(hSrc, 0);
			return false;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// ���̃`�����N��
		ret = mmioAscend(hSrc, &mSrcWaveData, 0);
	}


	// �T�E���h�o�b�t�@�̍쐬
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

	// ���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// �w�b�_�p���������J��
	free(wf);

	// WAV�����
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

	// COM�̏I��
	CoUninitialize();

	return true;
}
