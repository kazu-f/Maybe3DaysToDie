#pragma once
#include "SaveDataFile.h"

struct ToolInfo;
namespace nsTerrain {
	class TerrainChunkData;

	static const int NEAR_CHUNK_MAXCOUNT = 4;


	//�n�`�I�u�W�F�N�g�B
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;
		/// <summary>
		/// ���[���h���Z�b�g�B
		/// </summary>
		void AddTerrainChunk(TerrainChunkData* world);
		/// <summary>
		/// �I�u�W�F�N�g�f�[�^��R�Â��B
		/// </summary>
		void SetObjData(SaveDataFile::ObjectData* objData)
		{
			m_objData = objData;
		}

		/// <summary>
		/// �R���C�_�[�̓o�^���������邩�ǂ������v�Z�B
		/// </summary>
		bool IsTerrainEnabled()
		{
			return (m_voxel > 0.0f);
		}
		/// <summary>
		/// ���݂̑ϋv�l��ݒ�B
		/// </summary>
		/// <param name="durable"></param>
		void SetCurrentDurable(int durable)
		{
			m_params.Durable = min(durable, m_maxDurable);
		}
		/// <summary>
		/// �n�`�̃X�P�[�����Z�b�g�B
		/// </summary>
		/// <param name="scale"></param>
		void SetVoxel(float scale)
		{
			m_voxel = scale;
		}
		/// <summary>
		/// �n�`ID���Z�b�g�B
		/// </summary>
		/// <param name="id">id</param>
		void SetTerrainID(int id)
		{
			m_terrainId = id;
		}
		/// <summary>
		/// �{�N�Z���l���擾�B
		/// </summary>
		float GetVoxel()
		{
			return m_voxel;
		}
		/// <summary>
		/// �n�`ID���擾�B
		/// </summary>
		int GetTerrainID()
		{
			return m_terrainId;
		}
		/// <summary>
		/// �_���[�W��^����B
		/// </summary>
		int Damage(const ToolInfo& tool)override final;

		/// <summary>
		/// �u���b�N��ǉ�
		/// </summary>
		/// <param name="params">�p�����[�^</param>
		/// <param name="pos">�ʒu</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		void AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)override final;

		void CalcVoxel();

		void ResetTerrain()
		{
			m_params.BlockID = -1;
			ResetParams();
			m_maxDurable = 0;
			m_voxel = 0.0f;
			m_terrainId = -1;
			UpdateChunkData();
		}
	private:

		void UpdateChunkData();
	private:


	private:
		TerrainChunkData* m_chunkData[NEAR_CHUNK_MAXCOUNT] = { nullptr };		//�`�����N���B
		char m_terrainChunkDataSize = 0;											//�`�����N���̕ێ����B
		SaveDataFile::ObjectData* m_objData = nullptr;

		int m_terrainId = -1;		//�n�`id�ԍ��B
		float m_voxel = 0.0f;		//�{�N�Z���l�B

		//bool m_registColider = false;
	};

}
