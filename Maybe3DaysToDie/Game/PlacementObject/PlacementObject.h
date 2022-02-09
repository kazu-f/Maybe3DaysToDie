#pragma once
#include "DestructibleObject/Block/Block.h"
#include "MiniEngine/physics/CollisionAttr.h"

class LoadingByChunk;
class SaveDataFile;
namespace nsTerrain {
	class TerrainManager;
}

//todo �v���C���[������ĂԂ悤�ɂȂ�����IGameObject���p�����Ȃ��悤��
class PlacementObject:public IGameObject
{
public:
	PlacementObject();
	~PlacementObject();

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

	/// <summary>
	/// �I�u�W�F�N�g��ݒu
	/// </summary>
	void PlaceObject();

	/// <summary>
	/// �ݒu����I�u�W�F�N�g�̏��
	/// </summary>
	/// <param name="params">�p�����[�^</param>
	void SetParams(const ObjectParams& params)
	{
		if (ObjID == params.BlockID)
		{
			//�ύX�Ȃ�
			return;
		}
		objParam = params;
		if (SetModelParams())
		{
			m_ObjectModel->SetActiveFlag(true);
			m_ObjectModel->Init(m_modelInitData);
		}
		else
		{
			m_ObjectModel->SetActiveFlag(false);
		}
	}

	/// <summary>
	/// �`�����N�ǂݍ��ݏ������Z�b�g
	/// </summary>
	void SetLoadingChunk(LoadingByChunk* lbc)
	{
		m_LoadingChunk = lbc;
	}

	/// <summary>
	/// �Z�[�u�f�[�^�t�@�C�����Z�b�g
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}

private:
	/// <summary>
	/// �ݒu����I�u�W�F�N�g�̈ʒu���v�Z
	/// </summary>
	void CalcObjectPos();

	/// <summary>
	/// ���f�������݂̏��ŏ���������
	/// </summary>
	bool SetModelParams();

private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//�I�u�W�F�N�g���f��
	Vector3 m_pos = Vector3::Zero;		//���f���̃|�W�V����
	Vector3 m_scale = Vector3::One;		//���f���̃X�P�[��
	Quaternion m_qrot = Quaternion::Identity;		//���f���̉�]
	std::vector<Block*> m_model;
	bool CanPlace = false;
	DestructibleObject* m_hitObj = nullptr;
	LoadingByChunk* m_LoadingChunk = nullptr;
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//�e���C���}�l�[�W���[
	SaveDataFile* m_SaveData = nullptr;
	ObjectParams objParam;
	ModelInitData m_modelInitData;
	bool Enable = false;
	int ObjID = -1;
};

