#include "stdafx.h"
#include "MapLoad.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"

void MapLoad::Init(const char* filePath)
{
	for (auto& id : ChunkID)
	{
		if (id < 0 || id > MAX_CHUNK_SIDE)
		{
			//�`�����N�͈̔͊O�B
			//������ƃ`�����NID���Z�b�g���Ă��������B
			std::abort;
		}
	}
	for (int x = 0; x < ChunkHeight; x++)
	{
		for (int y = 0; y < ChunkHeight; y++)
		{
			if (y < GroundSurface)
			{
				continue;
			}
			for (int z = 0; z < ChunkHeight; z++)
			{
				auto& obj = m_SaveDataFile->m_ChunkData[ChunkID[0]][ChunkID[1]].ObjData[x][y][z];
				//���̃`�����N���Z�b�g
				obj.ObjId = 0;
				obj.ObjDurable = 0;
			}
		}
	}
	//tkl�t�@�C�������[�h
	m_tklFile.Load(filePath);
	//�{�[���s����\�z
	BuildBoneMatrices();

	for (auto& bone : m_bones)
	{
		if (bone->GetParentBoneNo() != 0)
		{
			//�e�����[�g�̏ꍇ�̂݃}�b�v�`�b�v�����B
			continue;
		}

		int boneHash = Util::MakeHash(bone->GetName());
		auto* block = m_itemDataFile->GetBlockDataHash(boneHash);
		GameItemPlaceObj* placeObj = nullptr;
		if (block == nullptr)
		{
			placeObj = m_itemDataFile->GetPlaceDataHash(boneHash);
			if (placeObj == nullptr)continue;
		} 

		SObjData objData;
		bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);
		//3dsMax�Ǝ����Ⴄ���߁A�␳������B
		//���W�B
		auto t = objData.position.y;
		objData.position.y = objData.position.z;
		objData.position.z = -t;
		//��]�B
		t = objData.rotation.y;
		objData.rotation.y = objData.rotation.z;
		objData.rotation.z = -t;

		auto& Obj = GetObjectArrange(objData.position);

		if (block != nullptr)
		{
			Obj.ObjDurable = block->GetObjParams().Durable;
			Obj.ObjDurable = block->GetObjParams().Durable;
			Obj.Rotate = objData.rotation;
		}
		else if (placeObj != nullptr)
		{
			Obj.ObjDurable = placeObj->GetObjParams().Durable;
			Obj.ObjDurable = placeObj->GetObjParams().Durable;
			Obj.Rotate = objData.rotation;
		}

		//for (int i = 0; i < BlockKinds; i++)
		//{
		//	if (wcscmp(bone->GetName(), m_SaveDataFile->ObjectFilePath[i].c_str()) == 0)
		//	{
		//		//�����񓙂����Ƃ�
		//		Obj.ObjDurable = 500;
		//		Obj.ObjId = i;
		//		Obj.Rotate = objData.rotation;
		//		break;
		//	}
		//}
	}
}

void MapLoad::BuildBoneMatrices()
{
	m_tklFile.QueryObject([&](auto& tklObj) {
		//�o�C���h�|�[�Y�B
		Matrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 0.0f;

		//�o�C���h�|�[�Y�̋t�s��B
		Matrix invBindPoseMatrix;
		memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
		memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
		memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
		memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
		invBindPoseMatrix.m[0][3] = 0.0f;
		invBindPoseMatrix.m[1][3] = 0.0f;
		invBindPoseMatrix.m[2][3] = 0.0f;
		invBindPoseMatrix.m[3][3] = 0.0f;
		//���C�h�����ɕϊ��B
		wchar_t boneName[256];
		mbstowcs(boneName, tklObj.name.get(), 256);
		BonePtr bone = std::make_unique<Bone>(
			boneName,
			bindPoseMatrix,
			invBindPoseMatrix,
			tklObj.parentNo,
			tklObj.no
			);

		m_bones.push_back(std::move(bone));
	});

	for (auto& bone : m_bones) {
		if (bone->GetParentBoneNo() != -1) {
			m_bones.at(bone->GetParentBoneNo())->AddChild(bone.get());
			//���[�J���}�g���N�X���v�Z�B
			const Matrix& parentMatrix = m_bones.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
			Matrix localMatrix;
			localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
			bone->SetLocalMatrix(localMatrix);
		}
		else {
			bone->SetLocalMatrix(bone->GetBindPoseMatrix());
		}
	}

	//�{�[���s����m��
	m_boneMatrixs = std::make_unique<Matrix[]>(m_bones.size());
	m_isInited = true;
}

SaveDataFile::ObjectData& MapLoad::GetObjectArrange(Vector3& pos)
{
	//�Z�[�u�f�[�^�t�@�C������`�����N�̏����擾
	auto& chunkData = m_SaveDataFile->m_ChunkData[ChunkID[0]][ChunkID[1]];

	//�|�W�V�����ɑΉ�����u���b�N���擾
	int id_x = pos.x / OBJECT_UNIT;
	id_x = static_cast<int>(id_x % ChunkWidth);
	id_x += ChunkWidth / 2;
	id_x = max(0, min(id_x, ChunkWidth - 1));

	int id_y = pos.y / OBJECT_UNIT;
	id_y = static_cast<int>(id_y % ChunkHeight);
	id_y += GroundSurface;
	id_y = min(id_y, ChunkHeight - 1);

	int id_z = pos.z / OBJECT_UNIT;
	id_z = static_cast<int>(id_z % ChunkWidth);
	id_z += ChunkWidth / 2;
	id_z = max(0, min(id_z, ChunkWidth - 1));

	return chunkData.ObjData[id_x][id_y][id_z];
}