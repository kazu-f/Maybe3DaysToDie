#pragma once

#include "MarchingCubeTable.h"
#include "Navigation/NVMGenerator.h"
#include "Enemy/EnemyGenerator.h"

namespace nsTerrain {

	static const float TERRAIN_UNIT = 100.0f;
	static const float TERRAIN_HALF_UNIT = 50.0f;

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

		bool Start()override final;
		void Update()override final;
		void OnDestroy()override final;
		void ForwardRender(RenderContext& rc) override final;

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
		static const int width = 64;
		static const int height = 16;
		float m_terrainSurface = 0.5f;

		float terrainMap[width + 1][height + 1][width + 1] = { 0.0f };
		CNoise m_perlinNoise;
		TerrainRender* m_terrainRender = nullptr;		//�n�`�`��N���X�B
		NVMGenerator m_NVMGenerator;					//NVM�����B
		EnemyGenerator m_enemyGenerator;				//enemyGenerator.
		std::vector<Vector3> m_vertices;				//���_�f�[�^�B
		CPhysicsStaticObject m_staticObj;				//�����I�u�W�F�N�g�B
	};

}