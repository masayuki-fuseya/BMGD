//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/12/02		
//!
//! @author M.Fuseya	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "GameMain.h"

#include "..\Scenes\GameBase.h"
#include "..\Scenes\GameLogo.h"
#include "..\Scenes\GameTitle.h"
#include "..\Scenes\GameSelect.h"
#include "..\Scenes\GamePlay.h"
#include "..\Scenes\GameClear.h"
#include "..\Scenes\GameOver.h"

// �v���g�^�C�v�錾 ====================================================


// �O���[�o���ϐ��̒�` ====================================================
GameBase* base;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::InitializeGame()
{
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::UpdateGame()
{
	//�V�[���Ǘ�
	if (NextScene != scene)
	{
		scene = NextScene;
		// �V�[���폜
		delete base;
		init = 0;

		//�V�[�����Ƃ̌Ăяo��
		switch (scene)
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
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::RenderGame()
{
	base->Render();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::FinalizeGame()
{
}