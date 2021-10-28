#include "stdafx.h"
#include "Block.h"

Block::~Block()
{
	ReleaseCol();
}