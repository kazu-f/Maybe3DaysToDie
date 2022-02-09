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

	private:
		std::vector<TexturePtr> m_terrainTextures;

	};

}
