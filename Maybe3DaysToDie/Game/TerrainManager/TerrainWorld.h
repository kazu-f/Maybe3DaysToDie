#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "Navigation/NVMGenerator.h"
#include "Enemy/EnemyGenerator.h"

namespace nsTerrain {


	class TerrainRender;

	union Cube {
		float cube[8];
	};

	class TerrainWorld : public IGameObject
	{
	public:
		TerrainWorld()
			:m_perlinNoise(2)
		{

		}
	private:
		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
		void ForwardRender(RenderContext& rc) override final;
	public:	//����̒n�`���擾����B
		Terrain& GetTerrain(const Vector3& pos);

		/// <summary>
		/// �n�`���X�V���ꂽ�B
		/// </summary>
		void EnableUpdated()
		{
			m_isUpdated = true;
		}

	private:
		/// <summary>
		/// �L���Ȓn�`�����֐��H�B
		/// </summary>
		void PopurerTerrainMap();		

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
			return (delta == 0.0f) ? m_terrainSurface : (m_terrainSurface - v1) / delta;

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
		static const int width = 16;
		static const int height = 8;
		float m_terrainSurface = 0.5f;

		Terrain m_terrainMap[width][height][width];
		CNoise m_perlinNoise;
		TerrainRender* m_terrainRender = nullptr;		//�n�`�`��N���X�B
		NVMGenerator m_NVMGenerator;					//NVM�����B
		EnemyGenerator m_enemyGenerator;				//enemyGenerator.
		std::vector<Vector3> m_vertices;				//���_�f�[�^�B
		CPhysicsStaticObject m_staticObj;				//�����I�u�W�F�N�g�B
		bool m_isUpdated = false;						//�n�`�̍X�V������B
	};

}