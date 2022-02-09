#pragma once

namespace nsTerrain {

	/// <summary>
	/// �n�`�̃}�e���A���B
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
