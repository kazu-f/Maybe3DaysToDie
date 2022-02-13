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
		m_terrainTextures.resize(MAX_TERRAIN_TEX);
	}

	TerrainMaterial::~TerrainMaterial()
	{
	}

	void TerrainMaterial::InitTexture()
	{
		int texNo = 0;
		for (auto& tex : m_terrainTextures)
		{
			const char* path = TERRAIN_TEX_PATHS[texNo];
			tex = ResourceEngine().GetTextureFromBank(path);
			if (tex == nullptr)
			{
				tex = new Texture;

				//文字列変換。
				wchar_t wddsFilePath[1024];
				mbstowcs(wddsFilePath, path, 1023);
				//テクスチャを読み込む。
				tex->InitFromDDSFile(wddsFilePath);
				ResourceEngine().RegistTextureToBank(path, tex);
			}

			texNo++;
		}
	}
}
