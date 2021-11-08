#pragma once
#include "DestructibleObject/Terrain/Terrain.h"
//todo [最適化]モデルの処理が重すぎるので最適化する
class IStage
{
public:
	IStage() 
	{
		m_Terrain.resize(ChunkWidth * ChunkWidth);
		m_model.resize(ChunkWidth * ChunkWidth);
	}
	virtual ~IStage() {}

	/// <summary>
	/// マップ生成
	/// </summary>
	virtual void CreateStage() = 0;

protected:
	std::vector<nsTerrain::Terrain*> m_Terrain = { nullptr };
	std::vector<prefab::ModelRender*> m_model = { nullptr };
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkWidth];
};