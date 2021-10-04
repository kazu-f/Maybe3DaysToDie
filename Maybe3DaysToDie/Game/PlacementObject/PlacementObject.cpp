#include "stdafx.h"
#include "PlacementObject.h"

PlacementObject::PlacementObject()
{

}

PlacementObject::~PlacementObject()
{

}

void PlacementObject::Awake()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);
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
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/WoodBlock.tkm";
	//m_ObjectModel->Init(m_modelInitData);
	return true;
}

void PlacementObject::Update()
{

}