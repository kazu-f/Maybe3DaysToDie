#include "MiniEngine.h"
#include "NullTextureMaps.h"

namespace Engine {
	void NullTextureMaps::Init()
	{
		//�e��e�N�X�`�������[�h�B
		auto TexLoad = [&](
			const char* loadTexFilePath,
			std::unique_ptr<char[]>& outTexData,
			unsigned int& outTexSize
			) {
				FILE* fp = fopen(loadTexFilePath, "rb");
				if (fp == nullptr) {
					//null�e�N�X�`���̃��[�h�Ɏ��s�B
					ENGINE_ASSERT(fp != nullptr,"null�e�N�X�`���̃��[�h�Ɏ��s���܂����B");
				}
				//�e�N�X�`���T�C�Y���v�Z�B
				fseek(fp, 0L, SEEK_END);
				outTexSize = ftell(fp);
				fseek(fp, 0L, SEEK_SET);

				//���������m��
				outTexData = std::make_unique<char[]>(outTexSize);
				fread(outTexData.get(), outTexSize, 1, fp);
				fclose(fp);
		};

		m_albedoMapFileName = "Assets/modelData/preset/NullAlbedo.dds";
		//�A���x�h�}�b�v�����[�h�B
		TexLoad(
			m_albedoMapFileName.c_str(),
			m_albedoMap,
			m_albedoMapSize);

		m_normalMapFileName = "Assets/modelData/preset/NullNormal.dds";
		//�@���}�b�v�����[�h�B
		TexLoad(
			m_normalMapFileName.c_str(),
			m_normalMap,
			m_normalMapSize);

		m_specularMapFileName = "Assets/modelData/preset/NullSpec.dds";
		//�X�y�L�����}�b�v�}�b�v�����[�h�B
		TexLoad(
			m_specularMapFileName.c_str(),
			m_specularMap,
			m_specularMapSize);

		m_reflectionMapFileName = "Assets/modelData/preset/NullReflection.dds";
		//���˃}�b�v�����[�h�B
		TexLoad(
			m_reflectionMapFileName.c_str(),
			m_reflectionMap,
			m_reflectionMapSize);

		m_refractionMapFileName = "Assets/modelData/preset/NullRefraction.dds";
		//���܃}�b�v�����[�h�B
		TexLoad(
			m_refractionMapFileName.c_str(),
			m_refractionMap,
			m_refractionMapSize);
	}
}
