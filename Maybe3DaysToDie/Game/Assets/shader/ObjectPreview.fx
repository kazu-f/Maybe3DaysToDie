#include "modelStruct.h"
#include "modelCB.h"

//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);
//サンプラステート。
sampler g_sampler : register(s0);

Texture2D<float4> shadowMap_0 : register(t6);		//シャドウマップ。
Texture2D<float4> shadowMap_1 : register(t7);		//シャドウマップ。
Texture2D<float4> shadowMap_2 : register(t8);		//シャドウマップ。

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
		binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;	//-1.0f～1.0fに調整。
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

//GBufferに書き込むピクセルシェーダーのエントリ関数。
PSOut_GBuffer PSMain(SPSIn psIn) {
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

	//反射率。
	Out.reflection = g_reflectionMap.Sample(g_sampler, psIn.uv).xy;

	return Out;
}