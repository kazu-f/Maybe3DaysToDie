#include "stdafx.h"
#include "PlacementObject.h"
#include "Load/TerrainLoad/LoadingByChunk.h"
#include "SaveDataFile.h"
#include "RayTest.h"
#include "Item/ItemDataFile.h"

PlacementObject::PlacementObject()
{
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
	for (auto model : m_model)
	{
		delete model;
	}
}

bool PlacementObject::Start()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);
	m_modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
	m_modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
	m_modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
	m_modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
	m_ObjectModel->SetForwardRenderFlag(true);
	m_ObjectModel->SetShadowCasterFlag(true);
	//�A�N�e�B�u��؂�
	m_ObjectModel->SetActiveFlag(false);

	return true;
}

void PlacementObject::Update()
{
	//�I�u�W�F�N�g��ݒu����ʒu���v�Z
	ObjID = static_cast<int>(objParam.BlockID);
	if (ObjID < 0 || ObjID > BlockKinds)
	{
		//�u���b�NID���}�C�i�X���ő�l���傫���Ƃ�return
		CanPlace = false;
		return;
	}
	CalcObjectPos();
	//�e��Z�b�g
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);
}

void PlacementObject::CalcObjectPos()
{
	//���_�̈ʒu
	Vector3 m_Start = MainCamera().GetPosition();
	//���������Ƀ|�W�V���������Z
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * SetRange;
	Vector3 cpos = MainCamera().GetPosition();
	Vector3 ctgt = MainCamera().GetTarget();
	Vector3 forward = cpos - ctgt;
	forward.Normalize();
	//���C�e�X�g�Ŏg�p����x�N�g�����쐬
	btVector3 start, end;
	start.setValue(m_Start.x, m_Start.y, m_Start.z);
	end.setValue(m_End.x, m_End.y, m_End.z);

	//���C�e�X�g
	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	//�ŏI�I�Ȉʒu
	Vector3 lastPos;
	lastPos.Set(end);
	//���C���Փ˂��Ă���Ƃ�
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		lastPos += callback.hitNormal * 100.0f;
		m_hitObj = ((DestructibleObject*)callback.ColObj->getUserPointer());
	}
	m_pos.Set(lastPos);
	CanPlace = false;
	if (m_pos.x >= 0.0f && m_pos.x <= (ChunkWidth - 1) * OBJECT_UNIT * MAX_CHUNK_SIDE)
	{
		if (m_pos.z >= 0.0f && m_pos.z <= (ChunkWidth - 1) * OBJECT_UNIT * MAX_CHUNK_SIDE)
		{
			if (m_pos.y >= 0.0f && m_pos.y <= (ChunkHeight - 1) * OBJECT_UNIT)
			{
				//�ʒu���͈͓��̎�
				CanPlace = callback.isHit;
			}
		}
	}
}

bool PlacementObject::SetModelParams()
{
	ObjID = static_cast<int>(objParam.BlockID);
	const auto& dataFile = ItemDataFile::GetInstance();
	if (ObjID < 0 || ObjID > BlockKinds)
	{
		//�u���b�NID���}�C�i�X���ő�l���傫���Ƃ�return
		return false;
	}
	else
	{
		const char* tkmPath = m_SaveData->ObjectFilePath[ObjID];
		m_modelInitData.m_tkmFilePath = tkmPath;
		return true;
	}
}

//todo [�œK��]��ŏ���������
void PlacementObject::PlaceObject()
{
	if (CanPlace)
	{
		if (m_hitObj != nullptr)
		{
			//�ݒu�\�Ȏ�
			Quaternion rot = Quaternion::Identity;
			Vector3 scale = Vector3::One;
			//�q�b�g���Ă���I�u�W�F�N�g�̈ʒu�Ƀu���b�N��ǉ�
			//m_hitObj->AddBlock(params, m_pos, rot, scale);

			//�ݒu����I�u�W�F�N�g�̃`�����NID���v�Z
			int ID[2] = { 0 };
			int x = m_pos.x / OBJECT_UNIT;
			ID[0] = static_cast<int>(x / ChunkWidth);
			int z = m_pos.z / OBJECT_UNIT;
			ID[1] = static_cast<int>(z / ChunkWidth);
			//�Ή�����u���b�N���擾
			//���C�e�X�g�ł���邱�Ƃ�����̂ŉ��ʂ��͂���
			Vector3 Pos = m_pos;
			Pos.x += OBJECT_UNIT / 4;
			Pos.y += OBJECT_UNIT / 4;
			Pos.z += OBJECT_UNIT / 4;

			Pos.x = abs(Pos.x);
			Pos.y = abs(Pos.y);
			Pos.z = abs(Pos.z);

			//�Z�[�u�f�[�^�t�@�C������`�����N�̏����擾
			auto& chunkData = m_SaveData->m_ChunkData[ID[0]][ID[1]];
			//�|�W�V�����ɑΉ�����u���b�N���擾
			int id_x = Pos.x / OBJECT_UNIT;
			id_x = static_cast<int>(id_x % ChunkWidth);
			int id_y = Pos.y / OBJECT_UNIT;
			id_y = static_cast<int>(id_y % ChunkHeight);
			int id_z = Pos.z / OBJECT_UNIT;
			id_z = static_cast<int>(id_z % ChunkWidth);
			
			//�Z�[�u�f�[�^�ɒ��ڏ�������
			chunkData.ObjData[id_x][id_y][id_z].ObjId = objParam.BlockID;
			chunkData.ObjData[id_x][id_y][id_z].ObjDurable = objParam.Durable;
			auto& block = m_LoadingChunk->GetChunkBlocks(ID).GetBlock(Pos);
			block.AddBlock(objParam, m_pos, rot, scale);
		}
	}
}