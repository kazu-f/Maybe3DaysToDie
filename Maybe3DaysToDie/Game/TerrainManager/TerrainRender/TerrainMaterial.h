#pragma once

namespace nsTerrain {
	struct TerrainTexPath {
		int hash = 0;
		std::string path;
	};
	/// <summary>
	/// �n�`�̃}�e���A���B
	/// </summary>
	class TerrainMaterial
	{
		using TexturePtr = std::unique_ptr<Texture>;
	public:
		TerrainMaterial();
		~TerrainMaterial();
		//�t�@�C���p�X��o�^����B
		void RegistTexturePath(std::string& texturePath);

		void InitTexture();

		Texture* GetTexture(int no)
		{
			return m_terrainTextures[no];
		}

	public:
		static const int MAX_TERRAIN_TEX = 4;

		int INIT_TEX_NUM = 0;		//�e�N�X�`���̐��B

	private:
		std::vector<Texture*> m_terrainTextures;
		std::vector<TerrainTexPath> m_terrainTexturePath;
	};

}
