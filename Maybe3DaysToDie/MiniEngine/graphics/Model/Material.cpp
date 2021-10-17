#include "MiniEngine.h"
#include "Material.h"
namespace Engine {
	//���[�g�V�O�l�`���ƃp�C�v���C���X�e�[�g����̓J���J���J��
	enum {
		enDescriptorHeap_CB,
		enDescriptorHeap_SRV,
		enNumDescriptorHeap
	};

	void IMaterial::InitTexture(const TkmFile::SMaterial& tkmMat)
	{
		const auto& nullTexMaps = GraphicsEngine()->GetNullTextureMaps();

		const char* filePath = nullptr;
		char* map = nullptr;
		unsigned int mapSize;

		//�A���x�h�}�b�v�B
		{
			if (tkmMat.albedoMap != nullptr) {
				filePath = tkmMat.albedoMapFileName.c_str();
				map = tkmMat.albedoMap.get();
				mapSize = tkmMat.albedoMapSize;
			}
			else {
				filePath = nullTexMaps.GetAlbedoMapFilePath();
				map = nullTexMaps.GetAlbedoMap().get();
				mapSize = nullTexMaps.GetAlbedoMapSize();
			}
			//�A���x�h�}�b�v�擾�B
			auto albedoMap = ResourceEngine().GetTextureFromBank(filePath);
			if (albedoMap == nullptr)
			{
				//�擾�ł��Ȃ���ΐV�����쐬���o�^�B
				albedoMap = new Texture;
				albedoMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, albedoMap);
			}
			m_albedoMap = albedoMap;
		}
		//�@���}�b�v�B
		{
			if (tkmMat.normalMap != nullptr) {
				filePath = tkmMat.normalMapFileName.c_str();
				map = tkmMat.normalMap.get();
				mapSize = tkmMat.normalMapSize;
			}
			else {
				filePath = nullTexMaps.GetNormalMapFilePath();
				map = nullTexMaps.GetNormalMap().get();
				mapSize = nullTexMaps.GetNormalMapSize();
			}
			//�@���}�b�v�擾�B
			auto normalMap = ResourceEngine().GetTextureFromBank(filePath);
			if (normalMap == nullptr)
			{
				//�擾�ł��Ȃ���ΐV�����쐬���o�^�B
				normalMap = new Texture;
				normalMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, normalMap);
			}
			m_normalMap = normalMap;
		}
		//�X�y�L�����}�b�v�B
		{
			if (tkmMat.specularMap != nullptr) {
				filePath = tkmMat.specularMapFileName.c_str();
				map = tkmMat.specularMap.get();
				mapSize = tkmMat.specularMapSize;
			}
			else {
				filePath = nullTexMaps.GetSpecularMapFilePath();
				map = nullTexMaps.GetSpecularMap().get();
				mapSize = nullTexMaps.GetSpecularMapSize();
			}
			//�X�y�L�����}�b�v�擾�B
			auto specMap = ResourceEngine().GetTextureFromBank(filePath);
			if (specMap == nullptr)
			{
				//�擾�ł��Ȃ���ΐV�����쐬���o�^�B
				specMap = new Texture;
				specMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, specMap);
			}
			m_specularMap = specMap;
		}
		//�X�y�L�����}�b�v�B
		{
			if (tkmMat.reflectionMap != nullptr) {
				filePath = tkmMat.reflectionMapFileName.c_str();
				map = tkmMat.reflectionMap.get();
				mapSize = tkmMat.reflectionMapSize;
			}
			else {
				filePath = nullTexMaps.GetReflectionMapFilePath();
				map = nullTexMaps.GetReflectionMap().get();
				mapSize = nullTexMaps.GetReflectionMapSize();
			}
			//�@���}�b�v�擾�B
			auto reflectionMap = ResourceEngine().GetTextureFromBank(filePath);
			if (reflectionMap == nullptr)
			{
				//�擾�ł��Ȃ���ΐV�����쐬���o�^�B
				reflectionMap = new Texture;
				reflectionMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, reflectionMap);
			}
			m_reflectionMap = reflectionMap;
		}

		//TODO:���t���N�V�����}�b�v�Ƌ��ܗ��}�b�v�̏������B
	}
	void IMaterial::InitConstantBuffer()
	{
		//�萔�o�b�t�@���쐬�B
		SMaterialParam matParam;
		matParam.hasNormalMap = m_normalMap->IsValid() ? 1 : 0;
		matParam.hasSpecMap = m_specularMap->IsValid() ? 1 : 0;
		matParam.hasReflectionMap = m_reflectionMap->IsValid() ? 1 : 0;
		m_constantBuffer.Init(sizeof(SMaterialParam), &matParam);
	}
	void IMaterial::InitFromTkmMaterila(
		const TkmFile::SMaterial& tkmMat,
		const SShaderInitData& shaderData)
	{
		//�e�N�X�`�������[�h�B
		InitTexture(tkmMat);
		//�萔�o�b�t�@���������B
		InitConstantBuffer();
	}
	void NonSkinMaterial::BeginRender(RenderContext& rc, int maxInstance)
	{
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);

		const auto renderStep = rc.GetRenderStep();

		switch (renderStep)
		{
		case enRenderStep_Undef:
			break;
		case enRenderStep_CreateDirectionalShadowMap:
			//�V���h�E�}�b�v�̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelShadowInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelShadowPipelineState);
			}
			break;
		case enRenderStep_PreRender:
			//G-Buffer�̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelPipelineState);
			}

			break;
		case enRenderStep_ForwardRender:
			//���������f���̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_transModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_transModelPipelineState);
			}

			break;
		default:
			break;
		}
	}
	void SkinMaterial::BeginRender(RenderContext& rc, int maxInstance)
	{
		rc.SetRootSignature(CPipelineStatesDefault::m_modelDrawRootSignature);

		const auto renderStep = rc.GetRenderStep();

		switch (renderStep)
		{
		case enRenderStep_Undef:
			break;
		case enRenderStep_CreateDirectionalShadowMap:
			//�V���h�E�}�b�v�̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelShadowInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelShadowPipelineState);
			}
			break;
		case enRenderStep_PreRender:
			//G-Buffer�̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelPipelineState);
			}

			break;
		case enRenderStep_ForwardRender:
			//���������f���̕`��B
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_transSkinModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_transSkinModelPipelineState);
			}

			break;
		default:
			break;
		}
	}
}