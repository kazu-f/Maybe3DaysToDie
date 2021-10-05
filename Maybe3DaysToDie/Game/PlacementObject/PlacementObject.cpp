#include "stdafx.h"
#include "PlacementObject.h"

PlacementObject::PlacementObject()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);
}

PlacementObject::~PlacementObject()
{

}

void PlacementObject::OnDestroy()
{
	if (m_ObjectModel != nullptr)
	{
		DeleteGO(m_ObjectModel);
		m_ObjectModel = nullptr;
	}
}

bool PlacementObject::Start()
{
	ModelInitData m_modelInitData;
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	m_ObjectModel->Init(m_modelInitData);
	//物理オブジェクトの作成
	CreatePhysics();
	return true;
}

void PlacementObject::Update()
{
	//各種セット
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);
}

void PlacementObject::CreatePhysics()
{
	//メッシュの作成
	m_StaticCol.CreateMesh(m_pos, m_qrot, m_scale, m_ObjectModel);
}