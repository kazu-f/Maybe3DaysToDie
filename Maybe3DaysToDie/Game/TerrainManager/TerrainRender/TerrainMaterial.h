#pragma once

namespace nsTerrain {

	/// <summary>
	/// 地形のマテリアル。
	/// </summary>
	class TerrainMaterial
	{
		using TexturePtr = std::unique_ptr<Texture>;
	public:
		TerrainMaterial();
		~TerrainMaterial();

		void InitTexture();

		Texture* GetTexture(int no)
		{
			return m_terrainTextures[no];
		}

	public:
		static const int MAX_TERRAIN_TEX = 4;

	private:
		std::vector<Texture*> m_terrainTextures;

	};

}
