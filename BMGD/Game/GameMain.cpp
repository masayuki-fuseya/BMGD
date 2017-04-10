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

#include "..\ADX2Le.h"
#include "CueSheet_0.h"

#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")


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
	m_base = new GameSelect;
	//�ǂݍ���
	ADX2Le::Initialize("Resources\\Sounds\\NewBMGD.acf");
	//���[�h
	ADX2Le::LoadAcb("Resources\\Sounds\\CueSheet_0.acb", "Resources\\Sounds\\CueSheet_0.awb");
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
	ADX2Le::Update();

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
	m_base->Update(&m_next_scene);
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
	ADX2Le::Finalize();
	if (m_base)
	{
		delete m_base;
		m_base = nullptr;
	}
}