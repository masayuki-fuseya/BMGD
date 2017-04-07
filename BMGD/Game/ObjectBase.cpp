//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.cpp
//!
//! @brief  �I�u�W�F�N�g�x�[�X�̃\�[�X�t�@�C��
//!
//! @date   2017/1/24		
//!
//! @author �g�����q	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//�w�b�_�t�@�C���̃C���N���[�h
#include "GameMain.h"

#include "ObjectBase.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//�����o�֐��̐錾

//grp_x��ݒ肷��
void ObjectBase::SetGrpX(int x)
{
	grp_x = x;
}

//grp_x�̒l���擾����
int ObjectBase::GetGrpX()
{
	return grp_x;
}

//grp_y��ݒ肷��
void ObjectBase::SetGrpY(int y)
{
	grp_y = y;
}

//grp_y�̒l��ݒ肷��
int ObjectBase::GetGrpY()
{
	return grp_y;
}

//grp_w��ݒ肷��
void ObjectBase::SetGrpW(int w)
{
	grp_w = w;
}

//grp_W���擾����
int ObjectBase::GetGrpW()
{
	return grp_w;
}

//grp_h��ݒ肷��
void ObjectBase::SetGrpH(int h)
{
	grp_h = h;
}

//grp_h���擾����
int ObjectBase::GetGrpH()
{
	return grp_h;
}

//pos_x��ݒ肷��
void ObjectBase::SetPosX(float x)
{
	pos_x = x;
}

//pos_x���擾����
float ObjectBase::GetPosX()
{
	return pos_x;
}

//pos_y��ݒ肷��
void ObjectBase::SetPosY(float y)
{
	pos_y = y;
}

//pos_y���擾����
float ObjectBase::GetPosY()
{
	return pos_y;
}

//spd_x��ݒ肷��
void ObjectBase::SetSpdX(float x)
{
	spd_x = x;
}

//spd_y���擾����
float ObjectBase::GetSpdX()
{
	return spd_x;
}

//spd_y��ݒ肷��
void ObjectBase::SetSpdY(float y)
{
	spd_y = y;
}

//spd_y���擾����
float ObjectBase::GetSpdY()
{
	return spd_y;
}

//state��ݒ肷��
void ObjectBase::SetState(int s)
{
	state = s;
}

//state���擾����
int ObjectBase::GetState()
{
	return state;
}


//�X�V�֐�
void ObjectBase::Update()
{
	pos_x = pos_x + spd_x;
	pos_y = pos_y + spd_y;
}

//�`��֐�
void ObjectBase::Render()
{
	RECT rect;


	rect = { grp_x,grp_y,grp_w,grp_h };
	g_spriteBatch->Draw(handle->m_pTexture, Vector2(pos_x, pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
}