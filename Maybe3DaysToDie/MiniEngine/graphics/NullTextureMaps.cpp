#include "MiniEngine.h"
#include "NullTextureMaps.h"

namespace Engine {
	void NullTextureMaps::Init()
	{
		//各種テクスチャをロード。
		auto TexLoad = [&](
			const char* loadTexFilePath,
			std::unique_ptr<char[]>& outTexData,
			unsigned int& outTexSize
			) {
				FILE* fp = fopen(loadTexFilePath, "rb");
				if (fp == nullptr) {
					//nullテクスチャのロードに失敗。
					ENGINE_ASSERT(
						fp != nullptr,
						"nullテクスチャのロードに失敗しました。\n"
						"%s",loadTexFilePath
					);
				}
				//テクスチャサイズを計算。
				fseek(fp, 0L, SEEK_END);
				outTexSize = ftell(fp);
				fseek(fp, 0L, SEEK_SET);

				//メモリを確保
				outTexData = std::make_unique<char[]>(outTexSize);
				fread(outTexData.get(), outTexSize, 1, fp);
				fclose(fp);
		};

		m_albedoMapFileName = "Assets/modelData/preset/NullAlbedo.dds";
		//アルベドマップをロード。
		TexLoad(
			m_albedoMapFileName.c_str(),
			m_albedoMap,
			m_albedoMapSize);

		m_normalMapFileName = "Assets/modelData/preset/NullNormal.dds";
		//法線マップをロード。
		TexLoad(
			m_normalMapFileName.c_str(),
			m_normalMap,
			m_normalMapSize);

		m_specularMapFileName = "Assets/modelData/preset/NullSpec.dds";
		//スペキュラマップマップをロード。
		TexLoad(
			m_specularMapFileName.c_str(),
			m_specularMap,
			m_specularMapSize);

		m_zeroValueMapFileName = "Assets/modelData/preset/ZeroValueTex.dds";
		//0マップをロード。
		TexLoad(
			m_zeroValueMapFileName.c_str(),
			m_zeroValueMap,
			m_zeroValueMapSize);
	}
}
