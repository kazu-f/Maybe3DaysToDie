#pragma once

#include "MarchingCubeTable.h"
#include "DestructibleObject/Terrain/Terrain.h"

namespace nsTerrain {
	class TerrainChunkData
	{
	public:
		void SetTerrainData(Terrain* terrain, const int x, const int y, const int z)
		{
			if (CheckChunkSize(x,y,z)) {
				m_terrainMap[x][y][z] = terrain;
				m_terrainMap[x][y][z]->SetTerrainChunk(this);
			}
		}
		/// <summary>
		/// �n�`�f�[�^���擾����B
		/// </summary>
		/// <param name="x">x�v�f</param>
		/// <param name="y">y�v�f</param>
		/// <param name="z">z�v�f</param>
		/// <returns></returns>
		Terrain* GetTerrainData(const int x, const int y, const int z)
		{
			if (CheckChunkSize(x, y, z)) {
				return m_terrainMap[x][y][z];
			}
			return nullptr;
		}
		/// <summary>
		/// �n�`�f�[�^���擾����B
		/// </summary>
		/// <param name="pos">�����^��3�v�f</param>
		/// <returns></returns>
		Terrain* GetTerrainData(const Vector3Int& pos)
		{
			if (CheckChunkSize(pos.x, pos.y, pos.z))
			{
				return m_terrainMap[pos.x][pos.y][pos.z];
			}
			return nullptr;
		}
	public:		//Update�t���O�B
		/// <summary>
		/// �n�`���X�V���ꂽ�B
		/// </summary>
		void EnableUpdated()
		{
			m_isUpdated = true;
		}
		/// <summary>
		/// �n�`�X�V�����������H
		/// </summary>
		bool IsUpdated()
		{
			return m_isUpdated;
		}
		/// <summary>
		/// �X�V�t���O�������B
		/// </summary>
		void ResetUpdated()
		{
			m_isUpdated = false;
		}
	private:	//�`�����N������p�֐��B
		/// <summary>
		/// �`�����N���Ɏ��܂��Ă��邩�ǂ����B
		/// </summary>
		/// <param name="x">x�v�f</param>
		/// <param name="y">y�v�f</param>
		/// <param name="z">z�v�f</param>
		/// <returns></returns>
		bool CheckChunkSize(int x,int y,int z)
		{
			return (
				CheckSize(ChunkWidth + 1, x)
				&& CheckSize(ChunkHeight, y)
				&& CheckSize(ChunkWidth + 1, z)
				);
		}

		bool CheckSize(int maxSize, int num)
		{
			return (num >= 0) && (num < maxSize);
		}
	private:
		Terrain* m_terrainMap[ChunkWidth + 1][ChunkHeight][ChunkWidth + 1] = { nullptr };
		bool m_isUpdated = false;						//�n�`�̍X�V������B
	};
}

