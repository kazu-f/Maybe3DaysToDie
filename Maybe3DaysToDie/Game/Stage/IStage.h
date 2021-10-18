#pragma once
#include "DestructibleObject/Terrain/Terrain.h"
//todo [最適化]モデルの処理が重すぎるので最適化する
class IStage
{
public:
	IStage() {}
	virtual ~IStage() {}

	/// <summary>
	/// マップ生成
	/// </summary>
	virtual void CreateStage() = 0;

protected:
	Terrain* m_Terrain = nullptr;
	prefab::ModelRender* m_model = nullptr;
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkDepth];
};