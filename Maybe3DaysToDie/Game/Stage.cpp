#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	//ここで地面を作る
	NewGround();
	//物理オブジェクト作成
	CreatePhysics();
	return true;
}

void Stage::Update()
{
	if (GetAsyncKeyState('A'))
	{
		m_stage.ReCreate();
	}
}

void Stage::OnDestroy()
{
	m_stage.OnDestroy();
	////モデルを削除
	//DeleteGO(m_Model);
}

void Stage::NewGround()
{
	m_stage.CreateStage();
	//m_Model = NewGO<prefab::ModelRender>(0);
	//ModelInitData InitModelUnity;
	//InitModelUnity.m_tkmFilePath = "Assets/modelData/testbg/bg.tkm";
	//m_Model->Init(InitModelUnity);
	//m_pos.x += 50.0f;
	//m_pos.z += 50.0f;
	//m_Model->SetPosition(m_pos);
	//m_Model->SetShadowReceiverFlag(true);
}

void Stage::CreatePhysics()
{
	////静的物理オブジェクトを作成
	//m_StaticCol.CreateMesh(m_pos, m_qrot, m_scale, m_Model);
}