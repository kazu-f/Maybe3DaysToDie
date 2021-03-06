/*
*		モデルシェーダー。
*/

#include "ShaderSampler.h"
#include "modelCB.h"
#include "LightStruct.h"
#include "modelStruct.h"
#include "PBR.h"
#include "Fog.h"
#include "CalcShadow.h"

//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);
//ボーン行列。
StructuredBuffer<float4x4> boneMatrix : register(t4);
//ディレクションライト。
StructuredBuffer<SDirectionalLight> directionalLight : register(t5);

StructuredBuffer<float4x4> instancingDatas : register(t9);		//インスタンシング描画用のデータ。
//サンプラステート。
//sampler g_sampler : register(s0);

//スキン行列を計算する関数。
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
		w += skinVert.Weights[i];
	}

	skinning += boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	return skinning;
}

//法線を計算。
float3 CalcNormal(float3 normal, float3 biNormal, float3 tangent, float2 uv)
{
	//法線の計算。
	float3 ret;
	if (hasNormalMap) {
		//法線マップから法線を引っ張ってくる。
		float3 binSpaceNormal = g_normalMap.Sample(g_sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;	//-1.0f〜1.0fに調整。
		binSpaceNormal = normalize(binSpaceNormal);
		ret = tangent * binSpaceNormal.x		//接線(法線に対して右？)
			+ biNormal * binSpaceNormal.y			//従法線(法線に対して上)
			+ normal * binSpaceNormal.z;			//法線方向
	}
	else {
		ret = normal;
	}
	return ret;
}

//頂点シェーダーのコア関数。
SPSIn VSMainCore(SVSIn vsIn, float4x4 wMat)
{
	SPSIn psIn;

	psIn.pos = mul(wMat, vsIn.pos);						//モデルの頂点をワールド座標系に変換。
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(wMat, vsIn.normal));		//法線をワールド座標系に変換。
	psIn.Tangent = normalize(mul(wMat, vsIn.Tangent));
	psIn.biNormal = normalize(mul(wMat, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキン無しモデル用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, mWorld);
}
/// <summary>
/// スキン無しインスタンモデル用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMainInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
	return VSMainCore(vsIn, instancingDatas[instanceID]);
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
SPSIn VSMainSkin(SVSIn vsIn)
{
	
	SPSIn psIn;

	float4x4 m;
	m = CalcSkinMatrix(vsIn.skinVert);

	psIn.pos = mul(m, vsIn.pos);						//モデルの頂点をワールド座標系に変換。
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(m, vsIn.normal));		//法線をワールド座標系に変換。
	psIn.Tangent = normalize(mul(m, vsIn.Tangent));
	psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/*
	スキンありインスタンシングモデル用の頂点シェーダー。
*/
SPSIn VSMainSkinInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SPSIn psIn;

	float4x4 m;
	m = CalcSkinMatrix(vsIn.skinVert);
	m = mul(instancingDatas[instanceID], m);

	psIn.pos = mul(m, vsIn.pos);						//モデルの頂点をワールド座標系に変換。
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(m, vsIn.normal));		//法線をワールド座標系に変換。
	psIn.Tangent = normalize(mul(m, vsIn.Tangent));
	psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

//ライトの輝度。
static const float LIGHT_LUMINANCE = float3(0.298912, 0.586611, 0.114478);

//物理ベースライティングのピクセルシェーダー。
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//return float4(1.0f,0.0f,0.0f,1.0f);
	//法線の計算。
	float3 normal = CalcNormal(psIn.normal,psIn.biNormal,psIn.Tangent,psIn.uv);
	float3 lig = 0;		//ライト
	float3 toEye = normalize(eyePos - psIn.worldPos);		//点から視点までの正規化ベクトル
	float metaric = 0.0f;			//金属度。
	float spec = 0.0f;
	float4 albedoColor = g_texture.Sample(g_sampler, psIn.uv);	//テクスチャカラー。		
	clip(albedoColor.a - 0.1f);

	if (hasSpecularMap) {
		//スペキュラマップがある。
		float4 specMap = g_specularMap.Sample(g_sampler, psIn.uv);
		metaric = specMap.r;
		spec = specMap.a;
	}
	float roughness = 1.0f - spec;			//拡散反射の面の粗さ。
	//シャドウ。
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	float shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		if (shadow < 0.9f) {
			//ディファード拡散反射の色。
			float3 baseColor = saturate(dot(normal, -directionalLight[ligNo].direction)) * directionalLight[ligNo].color.xyz / PI;
			//DisneyModel拡散反射
			float disneyDiffuse = NormalizedDisneyDiffuse(normal, -directionalLight[ligNo].direction, toEye, roughness);
			float3 diffuse = baseColor * disneyDiffuse;

			//クックトランスモデルの鏡面反射
			float ligLum = dot(LIGHT_LUMINANCE, directionalLight[ligNo].color.xyz);
			float specPower = CookTrranceSpecular(-directionalLight[ligNo].direction, toEye, normal, spec);
			//鏡面反射光の光は金属度が上がると、材質の色になる。
			float3 specCol = lerp(directionalLight[ligNo].color.xyz, albedoColor * ligLum, metaric) * specPower;

			//拡散反射光と鏡面反射光を線形補完。
			lig += lerp(diffuse, specCol, spec);
		}
	}
	//環境光。
	lig += ambientLight;

	/*lig += albedoColor * ambientLight / PI * (1.0f - metaric);
	lig += CookTrranceSpecular(normal, toEye, normal, metaric) * albedoColor * metaric;
	*/
	//lig *= lerp(1.0f, 0.5f, shadow);

	//最終的な色を決定する。

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;

	//霧の計算。
	float len = length(eyePos - psIn.worldPos);
	finalColor = CalcFog(finalColor, len);

	finalColor.a = albedoColor.a;
	return finalColor;
}

//GBufferに書き込むピクセルシェーダーのエントリ関数。
PSOut_GBuffer PSMain_RenderGBuffer (SPSIn psIn){
	PSOut_GBuffer Out = (PSOut_GBuffer)0;

	Out.albedo = g_texture.Sample(g_sampler, psIn.uv);		//アルベド。
	//Out.albedo = g_texture.SampleLevel(g_sampler, psIn.uv, 0);		//アルベド。
	//法線マップ。
	float3 normal = CalcNormal(psIn.normal, psIn.biNormal, psIn.Tangent, psIn.uv);
	Out.normal.xyz = (normal / 2.0f) + 0.5f;

	//ワールド座標。
	Out.worldPos = float4(psIn.worldPos, 0.0f);

	//スペキュラマップ。
	Out.specMap = 0.0f;
	if (hasSpecularMap) {
		//スペキュラマップがある。
		Out.specMap = g_specularMap.Sample(g_sampler, psIn.uv);
	}

	//シャドウ。
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

	//反射率。
	Out.reflection = g_reflectionMap.Sample(g_sampler, psIn.uv).xy;

	return Out;
}


/*
*	スキンなしモデルのシャドウマップ書き込み用の頂点シェーダー。
*/
SShadowMapPSIn VSMainNonSkinShadowMap(SShadowMapVSIn vsIn)
{
	SShadowMapPSIn psIn;
	psIn.pos = mul(mWorld, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}

/*
*	スキンなしインスタンシング描画モデルのシャドウマップ書き込み用の頂点シェーダー。
*/
SShadowMapPSIn VSMainNonSkinInstancingShadowMap(SShadowMapVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SShadowMapPSIn psIn;
	psIn.pos = mul(instancingDatas[instanceID], vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	スキンありモデルのシャドウマップ書き込み用の頂点シェーダー。
*/
SShadowMapPSIn VSMainSkinShadowMap(SShadowMapVSIn vsIn)
{
	SShadowMapPSIn psIn;
	float4x4 skinMatrix = CalcSkinMatrix(vsIn.skinVert);
	psIn.pos = mul(skinMatrix, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	スキンありインスタンシング描画モデルのシャドウマップ書き込み用の頂点シェーダー。
*/
SShadowMapPSIn VSMainSkinInstancingShadowMap(SShadowMapVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SShadowMapPSIn psIn;
	float4x4 skinMatrix = CalcSkinMatrix(vsIn.skinVert);
	float4x4 m = instancingDatas[instanceID];
	m = mul(m, skinMatrix);

	psIn.pos = mul(m, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	シャドウマップ書き込み用のピクセルシェーダー。
*/
float4 PSMainShadowMap(SShadowMapPSIn psIn) :SV_Target0
{
	float4 albedoColor = g_texture.Sample(g_sampler, psIn.uv);	//テクスチャカラー。		
	clip(albedoColor.a - 0.1f);

	return psIn.pos.z / psIn.pos.w;
}
