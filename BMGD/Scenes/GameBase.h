// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once


class GameBase
{
public:
	virtual ~GameBase() {}
	virtual void Update(int* next_scene) = 0;
	virtual void Render() = 0;
};

