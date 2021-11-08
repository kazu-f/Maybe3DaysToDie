#pragma once

#include "MiniEngine/MiniEngine.h"

//ツールの種類
enum ToolKinds {
	hand = 0,		//素手
	axe = 1 << 0,		//斧
	Pickaxe = 1 << 1,		//ツルハシ
	shovel = 1 << 2,		//ショベル
	others = 1 << 3,		//その他
	DebugTool = 0xffffffff,		//デバッグ用ツール
};

#include "DestructibleObject/DestructibleObject.h"

//チャンクのサイズ
const int ChunkWidth = 16;		//横幅
const int ChunkHeight = 8;		//高さ

const float SetRange = 500.0f;		//プレイヤーが届く範囲


using namespace Engine;
