#include "MiniEngine.h"
#include "Material.h"
namespace Engine {
	//ルートシグネチャとパイプラインステート周りはカリカリカリ
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

		//アルベドマップ。
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
			//アルベドマップ取得。
			auto albedoMap = ResourceEngine().GetTextureFromBank(filePath);
			if (albedoMap == nullptr)
			{
				//取得できなければ新しく作成し登録。
				albedoMap = new Texture;
				albedoMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, albedoMap);
			}
			m_albedoMap = albedoMap;
		}
		//法線マップ。
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
			//法線マップ取得。
			auto normalMap = ResourceEngine().GetTextureFromBank(filePath);
			if (normalMap == nullptr)
			{
				//取得できなければ新しく作成し登録。
				normalMap = new Texture;
				normalMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, normalMap);
			}
			m_normalMap = normalMap;
		}
		//スペキュラマップ。
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
			//スペキュラマップ取得。
			auto specMap = ResourceEngine().GetTextureFromBank(filePath);
			if (specMap == nullptr)
			{
				//取得できなければ新しく作成し登録。
				specMap = new Texture;
				specMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, specMap);
			}
			m_specularMap = specMap;
		}
		//スペキュラマップ。
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
			//法線マップ取得。
			auto reflectionMap = ResourceEngine().GetTextureFromBank(filePath);
			if (reflectionMap == nullptr)
			{
				//取得できなければ新しく作成し登録。
				reflectionMap = new Texture;
				reflectionMap->InitFromMemory(map, mapSize);
				ResourceEngine().RegistTextureToBank(filePath, reflectionMap);
			}
			m_reflectionMap = reflectionMap;
		}

		//TODO:リフレクションマップと屈折率マップの初期化。
	}
	void IMaterial::InitConstantBuffer()
	{
		//定数バッファを作成。
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
		//テクスチャをロード。
		InitTexture(tkmMat);
		//定数バッファを初期化。
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
			//シャドウマップの描画。
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelShadowInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelShadowPipelineState);
			}
			break;
		case enRenderStep_PreRender:
			//G-Bufferの描画。
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_ModelPipelineState);
			}

			break;
		case enRenderStep_ForwardRender:
			//半透明モデルの描画。
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
			//シャドウマップの描画。
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelShadowInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelShadowPipelineState);
			}
			break;
		case enRenderStep_PreRender:
			//G-Bufferの描画。
			if (maxInstance > 1) {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelInstancingPipelineState);
			}
			else {
				rc.SetPipelineState(CPipelineStatesDefault::m_SkinModelPipelineState);
			}

			break;
		case enRenderStep_ForwardRender:
			//半透明モデルの描画。
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