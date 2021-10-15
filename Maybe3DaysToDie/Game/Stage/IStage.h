#pragma once
#include "DestructibleObject/Terrain/Terrain.h"

class IStage
{
public:
	IStage() {}
	virtual ~IStage() {}

	/// <summary>
	/// É}ÉbÉvê∂ê¨
	/// </summary>
	virtual void CreateStage() = 0;

protected:
	Terrain* m_Terrain = nullptr;
	prefab::ModelRender* m_model[ChunkWidth][ChunkDepth] = { nullptr };
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkDepth];
};