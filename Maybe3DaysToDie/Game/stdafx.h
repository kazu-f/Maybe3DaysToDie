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
enum class ObjectType {
	Type = 0,
	Terrain = 1 << 0,
	Block = 1 << 1,
};

#include "DestructibleObject/DestructibleObject.h"
#include "nlohmann/json.hpp"						//jsonファイルを扱うためのヘッダ。

//チャンクのサイズ
const int ChunkWidth = 16;		//横幅
const int ChunkHeight = 8;		//高さ

const int MAX_CHUNK_SIDE = 64;		//ワールド全体の一辺にいくつチャンクがあるか

const float SetRange = 500.0f;		//プレイヤーが届く範囲

static const int BlockKinds = 4;		//ブロックの種類

using namespace Engine;
