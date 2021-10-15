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
		if (tkmMat.albedoMap != nullptr) {
			m_albedoMap.InitFromMemory(tkmMat.albedoMap.get(), tkmMat.albedoMapSize);
		}
		if (tkmMat.normalMap != nullptr) {
			m_normalMap.InitFromMemory(tkmMat.normalMap.get(), tkmMat.normalMapSize);
		}
		if (tkmMat.specularMap != nullptr) {
			m_specularMap.InitFromMemory(tkmMat.specularMap.get(), tkmMat.specularMapSize);
		}
		if (tkmMat.specularMap != nullptr) {
			m_reflectionMap.InitFromMemory(tkmMat.reflectionMap.get(), tkmMat.reflectionMapSize);
		}
		//TODO:���t���N�V�����}�b�v�Ƌ��ܗ��}�b�v�̏������B
	}
	void IMaterial::InitFromTkmMaterila(
		const TkmFile::SMaterial& tkmMat,
		const SShaderInitData& shaderData)
	{
		//�e�N�X�`�������[�h�B
		InitTexture(tkmMat);

		//�萔�o�b�t�@���쐬�B
		SMaterialParam matParam;
		matParam.hasNormalMap = m_normalMap.IsValid() ? 1 : 0;
		matParam.hasSpecMap = m_specularMap.IsValid() ? 1 : 0;
		matParam.hasReflectionMap = m_reflectionMap.IsValid() ? 1 : 0;
		m_constantBuffer.Init(sizeof(SMaterialParam), &matParam);
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