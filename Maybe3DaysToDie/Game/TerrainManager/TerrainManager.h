#pragma once

namespace Terrain {
	class Terrain;

	/// <summary>
	/// �n�`�Ǘ��I�u�W�F�N�g(�V���O���g���B)
	/// </summary>
	class TerrainManager : public IGameObject
	{
	private:
		//�V���O���g���B
		static TerrainManager* m_instance;
		TerrainManager()
		{
			m_instance = this;
			m_terrainPtrs.resize(MAX_TERRAIN_NUM,nullptr);
		}
		~TerrainManager()
		{
			m_instance = nullptr;
		}
	public:
		//�C���X�^���X�̍쐬�B
		static void CreateInstance()
		{
			ENGINE_ASSERT(m_instance == nullptr, "TerrainManager�������쐬����悤�Ƃ��Ă��܂��B");
			m_instance = NewGO<TerrainManager>(0);
		}
		//�C���X�^���X�̎擾�B
		static TerrainManager* GetInstance()
		{
			return m_instance;
		}

	public:
		/// <summary>
		/// �n�`�����B
		/// </summary>
		/// <param name="pos">���W�B</param>
		void CreateTerrain(const Vector3& pos);

	private:
		const int MAX_TERRAIN_NUM = 10000;				//10,000���x�����E���Ȃ��H

	private:
		using TerrainPtr = std::unique_ptr<Terrain>;
		std::vector<TerrainPtr> m_terrainPtrs;			//�n�`�B
		
	};

}
