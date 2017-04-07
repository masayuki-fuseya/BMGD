// 多重インクルードの防止 ==================================================
#pragma once


class GameBase
{
public:
	virtual ~GameBase() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
};

