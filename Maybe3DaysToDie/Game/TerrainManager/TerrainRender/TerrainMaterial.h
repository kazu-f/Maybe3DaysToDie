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
		//ファイルパスを登録する。
		void RegistTexturePath(std::string& texturePath, int itemID);

		Texture* GetTextureID(int id)
		{
			return m_terrainTextureMap[id];
		}

		Texture* GetTextureTypeID(int id)
		{
			Texture* tex;
			auto it = m_terrainTextureMap.begin();
			std::advance(it, id);

			tex = it->second;
			return tex;
		}

	public:
		static const int MAX_TERRAIN_TEX = 4;

		int GetTextureSize() {
			return m_terrainTextureMap.size();
		}

	private:
		std::map<int, Texture*> m_terrainTextureMap;
	};

}
