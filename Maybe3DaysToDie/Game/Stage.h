#pragma once
#include "Stage/SuperFlat/SuperFlat.h"
#include "Stage/Hill/Hill.h"
#include "Enemy/EnemyGenerator.h"
#include "TerrainManager/TerrainManager.h"
#include "SaveDataFile.h"

class Stage : public IGameObject
{
public:
	Stage();
private:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true��Ԃ��܂Ń��[�v����</returns>
	bool Start();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// delete������ƌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �n�ʂ�\������
	/// </summary>
	void NewGround();
public:
	/// <summary>
	/// �G�l�~�[�W�F�l���[�^�[���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyGenerator& GetEnemyGenerator()
	{
		return m_enemyGenerator;
	}

	nsTerrain::TerrainManager* GetTerrainWorld()
	{
		return m_Terrain;
	}

	WorldTableData* GetWorldTableData()
	{
		return &m_WorldTableData;
	}
private:
	//Hill m_stage;
	EnemyGenerator m_enemyGenerator;				//�G�l�~�[�W�F�l���[�^�[�B
	nsTerrain::TerrainManager* m_Terrain;
	WorldTableData m_WorldTableData;
	//prefab::ModelRender* m_Model = nullptr;		//�n��
	//CPhysicsStaticObject m_StaticCol;		//�ÓI�����I�u�W�F�N�g
	//Vector3 m_pos = Vector3::Zero;		//�|�W�V����
	//Quaternion m_qrot = Quaternion::Identity;		//��]
	//Vector3 m_scale = Vector3::One;		//�X�P�[��
};

