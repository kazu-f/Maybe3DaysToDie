#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	//ここで地面を作る
	NewGround();
	return true;
}

void Stage::Update()
{
}

void Stage::OnDestroy()
{
	//モデルを削除
	DeleteGO(m_Model);
}

void Stage::NewGround()
{
	m_Model = NewGO<prefab::ModelRender>(0);
	ModelInitData InitModelUnity;
	InitModelUnity.m_tkmFilePath = "Assets/modelData/testbg/bg.tkm";
	m_Model->Init(InitModelUnity);
}
