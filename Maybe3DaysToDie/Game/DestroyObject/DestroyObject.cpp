#include "stdafx.h"
#include "DestroyObject.h"
#include "TerrainManager/TerrainWorld.h"
#include "Tool/Tool.h"
#include "SaveDataFile.h"
#include "RayTest.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"
#include "Item/BlockItem.h"
#include "Item/GameItemTerrain.h"
#include "Item/GameItemMaterial.h"

DestroyObject::DestroyObject()
{

}

DestroyObject::~DestroyObject()
{

}

void DestroyObject::Update()
{
	if (Pad(0).IsTrigger(enButtonB))
	{
		AddObjectDamage();
	}
}

std::vector<Item>& DestroyObject::AddObjectDamage()
{
	//�z��N���A
	m_Item.clear();
	int damage = 0;
	int ObjectID = -1;

	//���_�̈ʒu
	Vector3 m_Start = MainCamera().GetPosition();
	//���������Ƀ|�W�V���������Z
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * PlayerRange * OBJECT_UNIT;
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
		//�n�`���擾
		//auto terrain = FindGO<nsTerrain::TerrainWorld>("Terrain");
		//�n�`�Ƀ_���[�W��^����
		//terrain->GetTerrain(lastPos).Damage(m_tool->GetInfo());
		DestructibleObject* obj = ((DestructibleObject*)callback.ColObj->getUserPointer());
		if (obj != nullptr)
		{
			ObjectParams param = obj->GetParam();
			if (param.Durable == 0)
			{
				return m_Item;
			}
			damage = obj->Damage(m_tool->GetInfo());
			param = obj->GetParam();
			//�I�u�W�F�N�g��ID
			ObjectID = param.BlockID;
			//�ݒu����I�u�W�F�N�g�̃`�����NID���v�Z
			int ID[2] = { 0 };
			int x = lastPos.x / OBJECT_UNIT;
			ID[0] = static_cast<int>(x / ChunkWidth);
			int z = lastPos.z / OBJECT_UNIT;
			ID[1] = static_cast<int>(z / ChunkWidth);
			//�Ή�����u���b�N���擾
			//���C�e�X�g�ł���邱�Ƃ�����̂ŉ��ʂ��͂���
			Vector3 Pos = lastPos;
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
			if (param.Durable > 0)
			{
				chunkData.ObjData[id_x][id_y][id_z].ObjId = ObjectID;
			}
			else
			{
				chunkData.ObjData[id_x][id_y][id_z].ObjId = 0;
			}
			chunkData.ObjData[id_x][id_y][id_z].ObjDurable = param.Durable;

		}
	}
	//�f�[�^�t�@�C���Q�b�g
	auto DataFile = ItemDataFile::GetInstance();
	auto* block = DataFile->GetBlockData(ObjectID);
	auto* terrain = DataFile->GetTerrainData(ObjectID);
	if (block != nullptr)
	{
		float maxdurable = block->GetObjParams().Durable;
		float ratio = damage / maxdurable;
		//�u���b�N
		for (auto& item : block->GetCollectItemData())
		{
			Item i;
			auto itemData = DataFile->GetMaterialData(item.collectID);
			i.item = itemData;
			i.stack = std::round(item.collectNum * ratio);
			m_Item.push_back(i);
		}
	}
	else if (terrain != nullptr)
	{
		float maxdurable = terrain->GetObjParams().Durable;
		float ratio = damage / maxdurable;
		//�e���C��
		for (auto& item : terrain->GetCollectItemData())
		{
			Item i;
			auto itemData = DataFile->GetMaterialData(item.collectID);
			i.item = itemData;
			i.stack = std::round(item.collectNum * ratio);
			m_Item.push_back(i);
		}
	}

	return m_Item;
}