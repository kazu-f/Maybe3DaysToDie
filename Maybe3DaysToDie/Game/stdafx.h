#pragma once

#include "MiniEngine/MiniEngine.h"

#include "DestructibleObject/DestructibleObject.h"

//チャンクのサイズ
const int ChunkWidth = 15;		//横幅
const int ChunkDepth = 15;		//奥行

const float SetRange = 500.0f;		//プレイヤーが届く範囲

//ツールの種類
enum ToolKinds {
	axe = 0,		//斧
	Pickaxe = 1 << 0,		//ツルハシ
	shovel = 1 << 1,		//ショベル
	others = 1 << 2,		//その他
	DebugTool = 0xffffffff		//デバッグ用ツール
};

using namespace Engine;
