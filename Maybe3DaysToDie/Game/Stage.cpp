#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	//�����Œn�ʂ����
	NewGround();
	return true;
}

void Stage::Update()
{
}

void Stage::OnDestroy()
{
	//���f�����폜
	DeleteGO(m_Model);
}

void Stage::NewGround()
{
	m_Model = NewGO<prefab::ModelRender>(0);
	ModelInitData InitModelUnity;
	InitModelUnity.m_tkmFilePath = "Assets/modelData/testbg/bg.tkm";
	m_Model->Init(InitModelUnity);
}
