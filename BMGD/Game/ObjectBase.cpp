//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.cpp
//!
//! @brief  オブジェクトベースのソースファイル
//!
//! @date   2017/1/24		
//!
//! @author 吉岡寿敏	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//ヘッダファイルのインクルード
#include "GameMain.h"

#include "ObjectBase.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//メンバ関数の宣言

//grp_xを設定する
void ObjectBase::SetGrpX(int x)
{
	grp_x = x;
}

//grp_xの値を取得する
int ObjectBase::GetGrpX()
{
	return grp_x;
}

//grp_yを設定する
void ObjectBase::SetGrpY(int y)
{
	grp_y = y;
}

//grp_yの値を設定する
int ObjectBase::GetGrpY()
{
	return grp_y;
}

//grp_wを設定する
void ObjectBase::SetGrpW(int w)
{
	grp_w = w;
}

//grp_Wを取得する
int ObjectBase::GetGrpW()
{
	return grp_w;
}

//grp_hを設定する
void ObjectBase::SetGrpH(int h)
{
	grp_h = h;
}

//grp_hを取得する
int ObjectBase::GetGrpH()
{
	return grp_h;
}

//pos_xを設定する
void ObjectBase::SetPosX(float x)
{
	pos_x = x;
}

//pos_xを取得する
float ObjectBase::GetPosX()
{
	return pos_x;
}

//pos_yを設定する
void ObjectBase::SetPosY(float y)
{
	pos_y = y;
}

//pos_yを取得する
float ObjectBase::GetPosY()
{
	return pos_y;
}

//spd_xを設定する
void ObjectBase::SetSpdX(float x)
{
	spd_x = x;
}

//spd_yを取得する
float ObjectBase::GetSpdX()
{
	return spd_x;
}

//spd_yを設定する
void ObjectBase::SetSpdY(float y)
{
	spd_y = y;
}

//spd_yを取得する
float ObjectBase::GetSpdY()
{
	return spd_y;
}

//stateを設定する
void ObjectBase::SetState(int s)
{
	state = s;
}

//stateを取得する
int ObjectBase::GetState()
{
	return state;
}


//更新関数
void ObjectBase::Update()
{
	pos_x = pos_x + spd_x;
	pos_y = pos_y + spd_y;
}

//描画関数
void ObjectBase::Render()
{
	RECT rect;


	rect = { grp_x,grp_y,grp_w,grp_h };
	g_spriteBatch->Draw(handle->m_pTexture, Vector2(pos_x, pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
}