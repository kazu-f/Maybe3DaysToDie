#pragma once
class IPlayerState: public IGameObject
{
	virtual void Init() = 0;
	virtual	void Update() = 0;
	virtual void Delete() = 0;
};

