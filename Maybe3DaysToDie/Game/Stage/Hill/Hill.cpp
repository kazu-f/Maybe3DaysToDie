#include "stdafx.h"
#include "Hill.h"
#include <random>

Hill::Hill()
{
	SetupRandomTable();
}

void Hill::OnDestroy()
{
	for (auto& ptr : m_model)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	for (auto& ptr : m_Terrain)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	//if (m_model != nullptr)
	//{
	//	DeleteGO(m_model);
	//	m_model = nullptr;
	//}
	//if (m_Terrain != nullptr)
	//{
	//	delete m_Terrain;
	//	m_Terrain = nullptr;
	//}
}

void Hill::CreateStage()
{
	//���f���̊e����
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";

	//�`�����N���ƂɃ}�b�v�𐶐�
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkWidth; Depth++)
		{
			prefab::ModelRender* m_ptr = NewGO<prefab::ModelRender>(0);
			m_ptr->Init(modelInitData);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			SetHeight(pos);
			m_ptr->SetPosition(pos);
			//�R���C�_�[���쐬
			CPhysicsStaticObject* col = nullptr;
			col = new CPhysicsStaticObject;
			col->CreateMesh(pos, Quaternion::Identity, Vector3::One, m_ptr);
			//�������m��
			nsTerrain::Terrain* t_ptr = new nsTerrain::Terrain();
			//�R���C�_�[�̍쐬
			//t_ptr->CreateCollider(m_ptr);
			//�z��ɒǉ�
			m_model.push_back(std::move(m_ptr));
			m_Terrain.push_back(std::move(t_ptr));
		}
	}

	////���f����new
	//m_model = NewGO<prefab::ModelRender>(0);
	////���f���̊e����
	//ModelInitData modelInitData;
	//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////���f����������
	//m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	////�`�����N���ƂɃ}�b�v�𐶐�
	//for (int Width = 0; Width < ChunkWidth; Width++)
	//{
	//	for (int Depth = 0; Depth < ChunkDepth; Depth++)
	//	{
	//		Vector3 pos = { 100.0f,0.0f,100.0f };
	//		pos.x *= Width;
	//		pos.z *= Depth;
	//		SetHeight(pos);
	//		m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
	//		//�R���C�_�[���쐬
	//		m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
	//	}
	//}
	//m_Terrain = new nsTerrain::Terrain;
	//m_Terrain->SetModel(m_model);
}

void Hill::SetHeight(Vector3& pos)
{
	//�p�[�����m�C�Y�Ŏg���l�����߂�
	int y = static_cast<int>(pos.y);
	float xSample = (pos.x + SeedX) / Relief;
	float zSample = (pos.z + SeedZ) / Relief;
	//�m�C�Y���p�[�����m�C�Y�ŏo�����l�ɂ���
	float noise = PerlinNoize(xSample, zSample);
	y = MaxHeight * noise;		//�������ő�l*noise�ɂ���
	y = static_cast<int>(y);
	//10�̈ʂ̗]������߂�
	float roundY = y % 100;
	//y��100���Ƃɂ���
	y -= roundY;
	//�l�̌ܓ�
	roundY /= 100.0f;
	roundY = round(roundY);
	roundY *= 100.0f;
	//y�ɉ��Z
	y += roundY;
	pos.y = static_cast<float>(y);
}

float Hill::PerlinNoize(float x,float y)
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
	//����
	Vector2 g00 = grad(xi, yi);
	Vector2 s00 = { xf,yf };
	float f00 = g00.Dot(s00);
	//�E��
	Vector2 g10 = grad(xi + 1.0f, yi);
	Vector2 s10 = { xf - 1.0f,yf };
	float f10 = g10.Dot(s10);
	//����
	Vector2 g01 = grad(xi, yi + 1.0f);
	Vector2 s01 = { xf, yf - 1.0f };
	float f01 = g01.Dot(s01);
	//�E��
	Vector2 g11 = grad(xi + 1.0f, yi + 1.0f);
	Vector2 s11 = { xf - 1.0f,yf - 1.0f };
	float f11 = g11.Dot(s11);

	//��莩�R�ȕω��������邽�߂̕␳
	float ux = fade(xf) * 1.0f;
	float uy = fade(yf) * 1.0f;

	//�㑤��2�_(00,10)�Ɖ�����2�_(01,11)���ꂼ��ł̉e���̕��ϒl
	float f0010 = lerpf(f00, f10, ux);
	float f0111 = lerpf(f01, f11, ux);
	//�ŏI�I�Ȏ��͂�4�_����̉e���l�̕���
	float fAve = lerpf(f0010, f0111, uy);

	return (fAve + 1.0f) / 2.0f;
}

void Hill::SetupRandomTable()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(-1.0, 1.0);
	//�����_���e�[�u������
	for (int i = 0; i < tableSize; i++)
	{
		float rx = distr(eng);
		float ry = distr(eng);
		Vector2 v1 = { rx,ry };
		Vector2 v2 = { 1.0f,1.0f };
		//-1.0 �` 1.0
		v1 = v1 * 2.0f;
		v1 = v1 - v2;
		randomTable[i] = v1;
	}
	for (int j = 0; j < tableSize; j++)
	{
		permX[j] = j;
		permY[j] = j;
	}
	//�z����V���b�t������
	shuffle(permX, tableSize);
	shuffle(permY, tableSize);
}

Vector2 Hill::grad(int x, int y)
{
	int pX = permX[int(x % tableSize)];
	int pY = permY[int((y + pX) % tableSize)];
	Vector2 returnVec = { randomTable[pY].x,randomTable[pY].y };
	return returnVec;
}

float Hill::fade(float t)
{
	if (easeFlg)
	{
		//6t^5 - 15t^4 + 10t^3
		return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
	}
	else
	{
		//3t^2 - 2t^3
		return t * t * (3.0f - 2.0f * t);
	}
}

void Hill::shuffle(int* array, int size)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	for (int i = 0; i < size; i++)
	{
		//i�`size�̃����_����int�𐶐�
		std::uniform_int_distribution<> distr(i,size);
		int r = distr(eng);
		int tmp = array[i];
		array[i] = array[r];
		array[r] = tmp;
	}
}