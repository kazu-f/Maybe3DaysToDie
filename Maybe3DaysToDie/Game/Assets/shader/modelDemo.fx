/*
*		モデルシェーダー。
*/

#include "modelCB.h"
#include "modelStruct.h"
#include "PBR.h"

cbuffer DemoCB : register(b4){
	int isPBR		: packoffset(c0.x);		//PBRを使うか。
	int isNormal	: packoffset(c0.y);		//法線マップを使うか。
	int isSpec		: packoffset(c0.z);		//スペキュラマップを使うか。
}

//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);
//ボーン行列。
StructuredBuffer<float4x4> boneMatrix : register(t4);
//ディレクションライト。
StructuredBuffer<SDirectionalLight> directionalLight : register(t5);

Texture2D<float4> shadowMap_0 : register(t6);		//シャドウマップ。
Texture2D<float4> shadowMap_1 : register(t7);		//シャドウマップ。
Texture2D<float4> shadowMap_2 : register(t8);		//シャドウマップ。

StructuredBuffer<float4x4> instancingDatas : register(t9);		//インスタンシング描画用のデータ。
//サンプラステート。
sampler g_sampler : register(s0);

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

/*
*	影が落ちているかを計算する。
*/
float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float shadow_val = tex.Sample(g_sampler, uv).r;
	if (depth > shadow_val + dOffset) {
		return 1.0f;
	}
	return 0.0f;
}

/*
*	カスケードインデックスの取得。
*/
int GetCascadeIndex(float zInView)
{
	[unroll]
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		if (zInView < shadowAreaDepthInViewSpace[i]) {
			return i;
		}
	}
	return -1;
}

/*
*	カスケードシャドウの処理。
*/
float CalcShadow(float3 worldPos, float zInView)
{
	float shadow = 0.0f;
	if (isShadowReceiver) {
		//影を落とす。
		//使用するシャドウマップ番号の取得。
		int cascadeIndex = GetCascadeIndex(zInView);
		if (cascadeIndex == -1) {
			return shadow;
		}

		float4 posInLVP = mul(mLVP[cascadeIndex], float4(worldPos, 1.0f));
		posInLVP.xyz /= posInLVP.w;

		float depth = min(posInLVP.z, 1.0f);

		//uv座標変換。
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);

		if (cascadeIndex == 0) {
			shadow = CalcShadowPercent(shadowMap_0, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.x);
		}
		if (cascadeIndex == 1) {
			shadow = CalcShadowPercent(shadowMap_1, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.y);
		}
		if (cascadeIndex == 2) {
			shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.z);
		}
	}
	return shadow;
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
		ret = tangent * binSpaceNormal.x		//接線(法線に対して右？)
			+ biNormal * binSpaceNormal.y			//従法線(法線に対して上)
			+ normal * binSpaceNormal.z;			//法線方向
	}
	else {
		ret = normal;
	}
	return ret;
}

float3 PhongSpec(float3 L,float3 Normal,float3 toEye, float3 Color,float specPow)
{
	//求めたtoEyeDirの反射ベクトルを求める。
	float3 reflectEyeDir = -toEye + 2 * dot(Normal, toEye) * Normal;
	//求めた反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
	float t = max(0.0f, dot(-L, reflectEyeDir));
	//pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
	float3 spec = pow(t, specPow) * Color;
	//?D スペキュラ反射が求まったら、ligに加算する。
	//鏡面反射を反射光に加算する。
	return spec;
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
//ライティングのピクセルシェーダー。
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//法線の計算。
	float3 normal = CalcNormal(psIn.normal,psIn.biNormal,psIn.Tangent,psIn.uv);
	float3 lig = 0;		//ライト
	float3 toEye = normalize(eyePos - psIn.worldPos);		//点から視点までの正規化ベクトル
	float metaric = 0.0f;			//金属度。
	float spec = 0.0f;
	float4 albedoColor = g_texture.Sample(g_sampler, psIn.uv);	//テクスチャカラー。		
	if (hasSpecularMap) {
		//スペキュラマップがある。
		float4 specMap = g_specularMap.Sample(g_sampler, psIn.uv);
		metaric = specMap.r;
		spec = specMap.a;
	}
	float roughness = 1.0f - spec;			//拡散反射の面の粗さ。
	//シャドウ。
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	float shadow = CalcShadow(psIn.worldPos, posInView.z);

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		if (shadow < 0.9f) {
			//ディファード拡散反射の色。
			float3 baseColor = max(dot(normal, -directionalLight[ligNo].direction), 0.0f) * directionalLight[ligNo].color.xyz / PI;

			float3 diffuse = 0.0f;
			float3 specCol = 0.0f;
			if (isPBR) {
				//DisneyModel拡散反射
				float disneyDiffuse = NormalizedDisneyDiffuse(normal, -directionalLight[ligNo].direction, toEye, roughness);
				diffuse = baseColor * disneyDiffuse;
				////クックトランスモデルの鏡面反射
				float ligLum = dot(LIGHT_LUMINANCE, directionalLight[ligNo].color.xyz);
				float specPower = CookTrranceSpecular(-directionalLight[ligNo].direction, toEye, normal, spec);
				float3 specCol = lerp(directionalLight[ligNo].color.xyz, albedoColor * ligLum, metaric) * specPower;
			}
			else {
				//通常の正規化ランバート拡散反射
				diffuse = baseColor;
				//フォン鏡面反射
				specCol = PhongSpec(directionalLight[ligNo].direction, normal, toEye, directionalLight[ligNo].color.xyz, 1.3f);
			}



			////拡散反射光と鏡面反射光を線形補完。
			lig += lerp(diffuse, specCol, metaric);

		}

	}
	//環境光。
	lig += ambientLight;

	//最終的な色を決定する。
	float4 finalColor = 1.0f;
	finalColor.xyz = albedoColor.xyz * lig;
	finalColor.a = albedoColor.a;
	return finalColor;
}

//GBufferに書き込むピクセルシェーダーのエントリ関数。
PSOut_GBuffer PSMain_RenderGBuffer(SPSIn psIn) {
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
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z);

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

	return psIn;
}
/*
*	シャドウマップ書き込み用のピクセルシェーダー。
*/
float4 PSMainShadowMap(SShadowMapPSIn psIn) :SV_Target0
{
	return psIn.pos.z / psIn.pos.w;
}
