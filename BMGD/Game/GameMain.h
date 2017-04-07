//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2016/12/02
//!
//! @author 
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
#include "..\Scenes\GameBase.h"

// �萔�̒�` ==============================================================

// �Q�[�����
#define SCREEN_WIDTH  640    // ��[pixel]
#define SCREEN_HEIGHT 480    // ����[pixel]


class GameMain
{
	private:
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

		GameBase* m_base;
		int m_scene;						//�V�[���Ǘ�
		int m_next_scene;					//���̃V�[��

	public:
		// �Q�[���̏���������
		GameMain();

		// �Q�[���̍X�V����
		void UpdateGame();

		// �Q�[���̕`�揈��
		void RenderGame();

		// �Q�[���̏I������
		~GameMain();
};

//�@�\���̐錾
//typedef struct tag_object
//{
//	Texture *handle;	//�O���t�B�b�N�n���h�� 
//	int grp_x;			//���摜�̂����W 
//	int grp_y;			//���摜�̂����W 
//	int grp_w;			//���摜�̕� 
//	int grp_h;			//���摜�̍��� 
//	float pos_x;		//���Wx 
//	float pos_y;		//���Wy 
//	float spd_x;		//���xx 
//	float spd_y;		//���xy 
//	int state;			//���
//	bool reversal;		//���E���]
//}OBJECT;				//�I�u�W�F�N�g�p