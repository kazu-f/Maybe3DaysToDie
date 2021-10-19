#pragma once
#include "DestructibleObject/Terrain/Terrain.h"
//todo [�œK��]���f���̏������d������̂ōœK������
class IStage
{
public:
	IStage() {}
	virtual ~IStage() {}

	/// <summary>
	/// �}�b�v����
	/// </summary>
	virtual void CreateStage() = 0;

protected:
	Terrain* m_Terrain = nullptr;
	prefab::ModelRender* m_model = nullptr;
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkDepth];
};