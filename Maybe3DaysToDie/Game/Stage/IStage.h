#pragma once
#include "DestructibleObject/Terrain/Terrain.h"
//todo [�œK��]���f���̏������d������̂ōœK������
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
	/// �}�b�v����
	/// </summary>
	virtual void CreateStage() = 0;

protected:
	std::vector<nsTerrain::Terrain*> m_Terrain = { nullptr };
	std::vector<prefab::ModelRender*> m_model = { nullptr };
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkWidth];
};