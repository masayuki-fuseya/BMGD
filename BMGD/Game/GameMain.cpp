//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/12/02		
//!
//! @author 	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "GameMain.h"

#include "..\Scenes\GameLogo.h"
#include "..\Scenes\GameTitle.h"
#include "..\Scenes\GameSelect.h"
#include "..\Scenes\GamePlay.h"
#include "..\Scenes\GameClear.h"
#include "..\Scenes\GameOver.h"

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
GameMain::GameMain()
{
	m_base = new GamePlay;
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
	if (m_next_scene != m_scene)
	{
		m_scene = m_next_scene;
		// �V�[���폜
		delete m_base;

		//�V�[�����Ƃ̌Ăяo��
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
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameMain::RenderGame()
{
	m_base->Render();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
GameMain::~GameMain()
{
	if (m_base)
	{
		delete m_base;
		m_base = nullptr;
	}
}