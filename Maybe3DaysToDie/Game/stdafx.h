#pragma once

#include "MiniEngine/MiniEngine.h"

//ツールの種類
enum ToolKinds {
	axe = 0,		//斧
	Pickaxe = 1 << 0,		//ツルハシ
	shovel = 1 << 1,		//ショベル
	others = 1 << 2,		//その他
	DebugTool = 0xffffffff,		//デバッグ用ツール
};

#include "DestructibleObject/DestructibleObject.h"

//チャンクのサイズ
const int ChunkWidth = 16;		//横幅
const int ChunkHeight = 8;		//高さ

const float SetRange = 500.0f;		//プレイヤーが届く範囲


using namespace Engine;
