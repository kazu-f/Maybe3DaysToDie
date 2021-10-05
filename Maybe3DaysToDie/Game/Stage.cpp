#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	//�����Œn�ʂ����
	NewGround();
	//�����I�u�W�F�N�g�쐬
	CreatePhysics();
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

void Stage::CreatePhysics()
{
	//�ÓI�����I�u�W�F�N�g���쐬
	m_StaticCol.CreateMesh(m_pos, m_qrot, m_scale, m_Model);
}