//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.h
//!
//! @brief  �I�u�W�F�N�g�x�[�X�̃w�b�_�[�t�@�C��
//!
//! @date   2017/1/24		
//!
//! @author �g�����q	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//���d�C���N���[�h�h�~
#pragma once


//�w�b�_�t�@�C���̃C���N���[�h
#include "..\Texture.h"


//�N���X�̒�`

class ObjectBase
{
protected:
	Texture* handle;
	int		grp_x;
	int		grp_y;
	int		grp_w;
	int		grp_h;
	float	pos_x;
	float	pos_y;
	float	spd_x;
	float	spd_y;
	int		state;

public:
	void	SetGrpX(int x);
	int		GetGrpX();

	void	SetGrpY(int y);
	int		GetGrpY();

	void	SetGrpW(int w);
	int		GetGrpW();

	void	SetGrpH(int h);
	int		GetGrpH();

	void	SetPosX(float x);
	float	GetPosX();

	void	SetPosY(float y);
	float	GetPosY();

	void	SetSpdX(float x);
	float	GetSpdX();

	void	SetSpdY(float y);
	float	GetSpdY();

	void	SetState(int s);
	int		GetState();

	void	Update();
	void	Render();
};

