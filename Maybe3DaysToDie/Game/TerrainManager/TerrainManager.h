#pragma once

namespace nsTerrain {
	class Terrain;

	/// <summary>
	/// �n�`�Ǘ��I�u�W�F�N�g(�V���O���g���B)
	/// </summary>
	class TerrainManager : public IGameObject
	{
	private:
		//�V���O���g���B
		static TerrainManager* m_instance;
	public:
		TerrainManager()
		{
			m_instance = this;
		}
		~TerrainManager()
		{
			m_instance = nullptr;
		}
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
	private:
		void Update()override final;
		void PostUpdate()override final;

	public:
		/// <summary>
		/// �n�`�����B
		/// </summary>
		/// <param name="pos">���W�B</param>
		Terrain* CreateTerrain(const Vector3& pos);

	private:
		const int MAX_TERRAIN_NUM = 10000;				//10,000���x�����E���Ȃ��H

	private:
		typedef std::unique_ptr<Terrain> TerrainPtr;
		std::vector<TerrainPtr> m_terrainPtrs;			//�n�`�B
		
	};

}
