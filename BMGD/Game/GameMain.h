//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2016/12/02
//!
//! @author M.Fuseya
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
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

// �萔�̒�` ==============================================================

// �Q�[���^�C�g��
#define GAME_TITLE "thousand"

// �Q�[�����
#define SCREEN_WIDTH  640    // ��[pixel]
#define SCREEN_HEIGHT 480    // ����[pixel]


//�@�\���̐錾
typedef struct tag_object
{
	Texture *handle;	//�O���t�B�b�N�n���h�� 
	int grp_x;			//���摜�̂����W 
	int grp_y;			//���摜�̂����W 
	int grp_w;			//���摜�̕� 
	int grp_h;			//���摜�̍��� 
	float pos_x;		//���Wx 
	float pos_y;		//���Wy 
	float spd_x;		//���xx 
	float spd_y;		//���xy 
	int state;			//���
	bool reversal;		//���E���]
}OBJECT;				//�I�u�W�F�N�g�p

//�@�񋓌^�錾
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

// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);


// �O���[�o���ϐ��̒�` ====================================================

EXTERN int g_key_code;						//�L�[���
EXTERN int g_key_old;						//�O�t���[���̃L�[���

EXTERN int g_scene;							//�V�[���Ǘ�
EXTERN int g_NextScene;						//���̃V�[��
EXTERN int g_init;							//�������Ǘ�