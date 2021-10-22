#include "LightStruct.h"
#include "PBR.h"

//地形用の定数バッファ
cbuffer TerrainCb : register(b0) {
	float4x4 mView			: packoffset(c0);
	float4x4 mProj			: packoffset(c4);
};

/*
*	ライト用の定数バッファ
*	tkLightManager.hのSLightParamと対応する。
*/
cbuffer lightCb : register(b1)
{
	float3 eyePos			: packoffset(c0);		//カメラの位置。
	int numDirectionLight : packoffset(c0.w);		//ディレクションライトの数。
	float3 ambientLight		: packoffset(c1);		//アンビエントライト。
	int numPointLight : packoffset(c1.w);		//ポイントライトの数。
	float4 screenParam		: packoffset(c2);		//スクリーンパラメータ(neae,far,screenW,screenH)
}

//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos : POSITION;		//地形の頂点座標。
	float3 normal : NORMAL;		//地形の法線。
	float2 uv : TEXCOORD0;		//UV座標。
};

struct SPSIn {
	float4 pos : SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal : NORMAL;		//法線。
	float2 uv : TEXCOORD0;		//UV座標。
};

Texture2D<float4> g_albedoMap : register(t0);	//アルベド
StructuredBuffer<SDirectionalLight> directionalLight : register(t1);	//ライト。

//サンプラステート。
sampler g_sampler : register(s0);

/// <summary>
/// 地形用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psIn;

	psIn.pos = mul(mView, vsIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = vsIn.normal;
	psIn.uv = vsIn.uv;

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//アルベド。
	float3 normal = psIn.normal;

	float3 lig = float3(0.0f,0.0f,0.0f);		//ライト

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		//ディファード拡散反射の色。
		float3 baseColor = saturate(dot(normal, -directionalLight[ligNo].direction)) * directionalLight[ligNo].color.xyz / PI;

		//拡散反射光と鏡面反射光を線形補完。
		lig += baseColor;
	}

	//環境光。
	lig += ambientLight;

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.xyz = float3(0.0f,1.0f,0.0f) * lig;
	finalColor.a = 1.0f;

	return finalColor;
}

