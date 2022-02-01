#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Navigation/NVMGenerator.h"
#include "TerrainChunkData.h"

namespace nsTerrain {


	class TerrainRender;
	class TerrainChunkData;

	union Cube {
		float cube[8];
	};

	class TerrainWorld : public IGameObject
	{
	public:

	private:
		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
		void ForwardRender(RenderContext& rc) override final;
	
	public:
		/// <summary>
		/// �i�r���b�V���𐶐�����B
		/// </summary>
		void CreateNVM();

		/// <summary>
		/// �n�`���f�[�^��o�^�B
		/// </summary>
		bool SetTerrainChunkData(TerrainChunkData* terrainCD);

		/// <summary>
		/// �n�`�̍��W��ݒ肷��B
		/// </summary>
		void SetTerrainPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// �n�`�`��N���X���擾�B
		/// </summary>
		TerrainRender* GetTerrainRender()
		{
			return m_terrainRender;
		}
		/// <summary>
		/// �������ς݂��ǂ����B
		/// </summary>
		bool IsInited()
		{
			return m_isInited;
		}

		/// <summary>
		/// nvm���X�V���邩�B
		/// </summary>
		/// <returns></returns>
		bool IsUpdateNvm()
		{
			return m_isUpdateNvm;
		}

		/// <summary>
		/// nvm�t���O�����Z�b�g�B
		/// </summary>
		void ResetUpdateNvmFlag()
		{
			m_isUpdateNvm = false;
		}

	public:	//����̒n�`���擾����B
		Terrain& GetTerrain(const Vector3& pos);
		Terrain& GetTerrain(const int pos[3]);

	private:
		//�O�p�`�e�[�u���̃C���f�b�N�X���擾�B
		int GetCubeConfihuration(const Cube& cube);

		//���b�V���f�[�^�\�z�B
		void CreateMeshData();		

		/// <summary>
		/// �}�[�`���O�L���[�u�̎O�p�`���\���B
		/// </summary>
		/// <param name="position">����������W�B</param>
		/// <param name="configIndex">�O�p�`�̐����p�^�[���ԍ��B</param>
		void MarchCube(Vector3 position, const Cube& cube);

		/// <summary>
		/// �R���C�_�[�̍Đ����B
		/// </summary>
		void CreateCollider();

		//�I�t�Z�b�g���v�Z�B
		float GetOffset(float v1, float v2)
		{
			float delta = v2 - v1;
			return (delta == 0.0f) ? nsMarching::TERRAIN_SURFACE : (nsMarching::TERRAIN_SURFACE - v1) / delta;

			//float ret = 0.0f;
			//float weight = v1 + v2;
			//if (v1 > v2)
			//{
			//	ret = m_terrainSurface * v1 / weight;
			//}
			//else if(v1 < v2){
			//	ret = 1.0f - m_terrainSurface * v2 / weight;
			//}
			//else if (v1 == v2)
			//{
			//	ret = m_terrainSurface;
			//}

			//return ret;
		}

	private:
		//static const int width = 16;
		//static const int height = 8;

		TerrainChunkData* m_terrainChunkData = nullptr;
		TerrainRender* m_terrainRender = nullptr;		//�n�`�`��N���X�B
		std::vector<Vector3> m_vertices;				//���_�f�[�^�B
		CPhysicsStaticObject m_staticObj;				//�����I�u�W�F�N�g�B
		Vector3 m_position = Vector3::Zero;				//���W�B

		std::vector<NVMGenerator::Cell> m_cellList;		//�Z�����X�g�B
		bool m_isNVMDebug = true;						//�f�o�b�O�`�悷��H
		bool m_isUpdateNvm = false;						//nvm������������H
		NVMDebugDraw* m_nvmDebugDraw = nullptr;			//�f�o�b�O�`��B

		bool m_isInited = false;						//�������ς݃t���O�B
	};

}