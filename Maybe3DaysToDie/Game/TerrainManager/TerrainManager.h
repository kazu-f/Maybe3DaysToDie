#pragma once

namespace Terrain {
	class Terrain;

	/// <summary>
	/// 地形管理オブジェクト(シングルトン。)
	/// </summary>
	class TerrainManager : public IGameObject
	{
	private:
		//シングルトン。
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
		//インスタンスの作成。
		static void CreateInstance()
		{
			ENGINE_ASSERT(m_instance == nullptr, "TerrainManagerが複数作成されようとしています。");
			m_instance = NewGO<TerrainManager>(0);
		}
		//インスタンスの取得。
		static TerrainManager* GetInstance()
		{
			return m_instance;
		}

	public:
		/// <summary>
		/// 地形生成。
		/// </summary>
		/// <param name="pos">座標。</param>
		void CreateTerrain(const Vector3& pos);

	private:
		const int MAX_TERRAIN_NUM = 10000;				//10,000程度が限界かなぁ？

	private:
		using TerrainPtr = std::unique_ptr<Terrain>;
		std::vector<TerrainPtr> m_terrainPtrs;			//地形。
		
	};

}
