#pragma once

#include "MarchingCubeTable.h"

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


	private:
		static const int width = 16;
		static const int height = 8;
		float terrainSurface = 0.5f;

		float terrainMap[width + 1][height + 1][width + 1] = { 0.0f };
		CNoise m_perlinNoise;
		TerrainRender* m_terrainRender = nullptr;		//�n�`�`��N���X�B

	};

}