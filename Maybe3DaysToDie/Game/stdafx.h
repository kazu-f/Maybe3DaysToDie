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
	Terrain = 0,		//地形
	Block = 1<<0,		//ブロック
};

//アクセスできるオブジェクトの種類
enum class AccessTag {
	NonAccess = 0,		//アクセスできない
	Root = 1 << 0,		//ルート
};

#include "DestructibleObject/DestructibleObject.h"
#include "nlohmann/json.hpp"						//jsonファイルを扱うためのヘッダ。

//チャンクのサイズ
const int ChunkWidth = 16;		//横幅
const int ChunkHeight = 8;		//高さ

const int GroundSurface = 3;		//地表

const int MAX_CHUNK_SIDE = 64;		//ワールド全体の一辺にいくつチャンクがあるか

const float SetRange = 500.0f;		//プレイヤーが届く範囲

static const int BlockKinds = 5;		//ブロックの種類

static const int Inventory_X = 7;
static const int Inventory_Y = 6;

//ゲーム中にロードしているチャンクの範囲
static const int LoadingChunkCols = 3;
static const int LoadingChunks = 3;

using namespace Engine;

#include "MauseInfo.h"