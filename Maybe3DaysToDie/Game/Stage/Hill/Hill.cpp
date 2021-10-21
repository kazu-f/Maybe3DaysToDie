#include "stdafx.h"
#include "Hill.h"

void Hill::OnDestroy()
{
	if (m_model != nullptr)
	{
		DeleteGO(m_model);
		m_model = nullptr;
	}
	if (m_Terrain != nullptr)
	{
		delete m_Terrain;
		m_Terrain = nullptr;
	}
}

void Hill::CreateStage()
{
	//���f����new
	m_model = NewGO<prefab::ModelRender>(0);
	//���f���̊e����
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	//���f����������
	m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
			//�R���C�_�[���쐬
			m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
		}
	}
	m_Terrain = new nsTerrain::Terrain;
	m_Terrain->SetModel(m_model);
}

void Hill::SetHeight(Vector3 pos)
{
	//�p�[�����m�C�Y�Ŏg���l�����߂�
	float y = 0.0f; // y��0�ɂ���
	float xSample = (pos.x + SeedX) / Relief;
	float zSample = (pos.z + SeedZ) / Relief;
	//�m�C�Y���p�[�����m�C�Y�ŏo�����l�ɂ���
}

void Hill::PerlinNoize(float x,float y)
{
	//�؂�̂ĂĐ����ɂ���
	int xi = static_cast<int>(x);
	int yi = static_cast<int>(y);

	//�����̍��W����̋���
	float xf = (x - xi);
	float yf = (y - yi);

	//���͂�4�̍��W���Ƃ̉e���l�����z�x�N�g���Ƌ����x�N�g���̓��ςŋ��߂�
	//gXX �e�_�̌��z�x�N�g��
	//sXX �e�_���獡���Ă�����W���w���x�N�g��
	//vXX gXX��sXX�̓���
	Vector2 g00 = grad(xi, yi);
	Vector2 s00 = { xf,yf };
	float v00 = g00.Dot(s00);
}

Vector2 Hill::grad(int x, int y)
{

}