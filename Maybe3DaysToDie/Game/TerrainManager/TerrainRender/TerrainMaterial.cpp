#include "stdafx.h"
#include "TerrainMaterial.h"

namespace nsTerrain {

	namespace {
		const char* TERRAIN_TEX_PATHS[TerrainMaterial::MAX_TERRAIN_TEX] =
		{
			"Assets/modelData/CubeBlock/T_GroundDirt_01_D.DDS",
			"Assets/modelData/Terrain/DirtTexture.dds",
			"Assets/modelData/Terrain/T_Ground_Grass_D.dds",
			"Assets/modelData/Terrain/T_MacroVariation.dds"
		};
	}

	TerrainMaterial::TerrainMaterial()
	{
		//m_terrainTextures.resize(MAX_TERRAIN_TEX);
	}

	TerrainMaterial::~TerrainMaterial()
	{
	}

	void TerrainMaterial::RegistTexturePath(std::string& texturePath)
	{
		int hash = Util::MakeHash(texturePath.c_str());

		//���̃e�N�X�`���p�X���o�^����Ă��邩�B
		auto it = std::find_if(m_terrainTexturePath.begin(), m_terrainTexturePath.end(), [&](TerrainTexPath& path)
			{
				return path.hash == hash;
			}
		);

		if (it == m_terrainTexturePath.end())
		{
			m_terrainTexturePath.push_back({ hash, texturePath });
		}
	}

	void TerrainMaterial::InitTexture()
	{
		//int texNo = 0;
		//for (auto& tex : m_terrainTextures)
		//{
		//	const char* path = TERRAIN_TEX_PATHS[texNo];
		//	tex = ResourceEngine().GetTextureFromBank(path);
		//	if (tex == nullptr)
		//	{
		//		tex = new Texture;

		//		//������ϊ��B
		//		wchar_t wddsFilePath[1024];
		//		mbstowcs(wddsFilePath, path, 1023);
		//		//�e�N�X�`����ǂݍ��ށB
		//		tex->InitFromDDSFile(wddsFilePath);
		//		ResourceEngine().RegistTextureToBank(path, tex);
		//	}

		//	texNo++;
		//}

		for (auto texPath : m_terrainTexturePath)
		{
			const char* path = texPath.path.c_str();
			Texture* tex = ResourceEngine().GetTextureFromBank(path);
			if (tex == nullptr)
			{
				tex = new Texture;

				//������ϊ��B
				wchar_t wddsFilePath[1024];
				mbstowcs(wddsFilePath, path, 1023);
				//�e�N�X�`����ǂݍ��ށB
				tex->InitFromDDSFile(wddsFilePath);
				ResourceEngine().RegistTextureToBank(path, tex);
			}
			m_terrainTextures.push_back(tex);
		}

		INIT_TEX_NUM = m_terrainTextures.size();
	}
}
