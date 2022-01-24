#pragma once
#include "GameItemBase.h"

class BlockItem :public GameItemBase
{
public:
	BlockItem() : GameItemBase(a, a,a) {}
	~BlockItem() {}

private:
	std::string a = nullptr;
};