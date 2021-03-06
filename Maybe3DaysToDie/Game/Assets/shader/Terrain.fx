#include "ShaderSampler.h"
#include "LightStruct.h"
#include "PBR.h"
#include "GBufferStruct.h"
#include "CalcShadow.h"

//地形用の定数バッファ
cbuffer TerrainCb : register(b0) {
	float4x4 mWorld			: packoffset(c0);
	float4x4 mView			: packoffset(c4);
	float4x4 mProj			: packoffset(c8);
	int isShadowReceiver	: packoffset(c12.x);		//シャドウレシーバー。
};

//地形用の定数バッファ
cbuffer TerrainShadowCb : register(b0) {
	float4x4 mWorldShadow			: packoffset(c0);
	float4x4 mTerrainLVP			: packoffset(c4);
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

//Terrain頂点シェーダーへの入力。
struct SVSInTerrain {
	float4 pos : POSITION;		//地形の頂点座標。
	float3 normal : NORMAL;		//地形の法線。
	float2 uv : TEXCOORD0;		//UV座標。
	float texType[8] : TEXTYPE;		//テクスチャを切り替えるための変数。
};

struct SPSInTerrain {
	float4 pos : SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal : NORMAL;		//法線。
	float2 uv : TEXCOORD0;		//UV座標。
	float3 worldPos : TEXCOORD1;	//ワールド空間でのピクセルの座標。
	float texType[8] : TEXCOORD2;		//テクスチャを切り替えるための変数。
};

Texture2D<float4> g_albedoMap : register(t0);	//アルベド
StructuredBuffer<SDirectionalLight> directionalLight : register(t1);	//ライト。

Texture2D<float4> g_terrainMap[4] : register(t10);	//地形用のテクスチャ

//Texture2D<float4> g_terrainMap1 : register(t10);	//地形用のテクスチャ
//Texture2D<float4> g_terrainMap2 : register(t11);	//地形用のテクスチャ
//Texture2D<float4> g_terrainMap3 : register(t12);	//地形用のテクスチャ
//Texture2D<float4> g_terrainMap4 : register(t13);	//地形用のテクスチャ

//サンプラステート。
//sampler g_sampler : register(s0);

float4 CalcTerrainTexture(float2 uv,float type[8])
{
	float4 finalCol = 0.0f;
	//finalCol += g_terrainMap1.Sample(g_sampler, uv) * type[0].x;		//アルベド。
	//finalCol += g_terrainMap2.Sample(g_sampler, uv) * type[0].y;		//アルベド。
	//finalCol += g_terrainMap3.Sample(g_sampler, uv) * type[0].z;		//アルベド。
	//finalCol += g_terrainMap4.Sample(g_sampler, uv) * type[0].w;		//アルベド。

	for (int i = 0; i < 4; i++)
	{
		finalCol += g_terrainMap[i].Sample(g_sampler, uv) * type[i];		//アルベド。

	}

	//finalCol += g_terrainMap[0].Sample(g_sampler, uv) * type[0];		//アルベド。
	//finalCol += g_terrainMap[1].Sample(g_sampler, uv) * type[1];		//アルベド。
	//finalCol += g_terrainMap[2].Sample(g_sampler, uv) * type[2];		//アルベド。
	//finalCol += g_terrainMap[3].Sample(g_sampler, uv) * type[3];		//アルベド。

	return finalCol;
}

/// <summary>
/// 地形用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSInTerrain VSTerrainMain(SVSInTerrain vsIn)
{
	SPSInTerrain psIn;

	psIn.pos = mul(mWorld, vsIn.pos);						//頂点をワールド座標系に変換。
	psIn.worldPos = psIn.pos;								//ワールド座標を入れる。
	psIn.pos = mul(mView, psIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = vsIn.normal;
	psIn.uv = vsIn.uv;
	//psIn.texType[0] = vsIn.texType[0];
	//psIn.texType[1] = vsIn.texType[1];
	for (int i = 0; i < 8; i++)
	{
		psIn.texType[i] = vsIn.texType[i];
	}

	return psIn;
}

//ライトの輝度。
static const float LIGHT_LUMINANCE = float3(0.298912, 0.586611, 0.114478);
float4 PSTerrainMain(SPSInTerrain psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//アルベド。
	float3 normal = psIn.normal;
	float3 toEye = normalize(eyePos - psIn.worldPos);		//点から視点までの正規化ベクトル
	float metaric = 0.0f;			//金属度。
	float spec = 0.0f;
	float roughness = 1.0f - spec;			//拡散反射の面の粗さ。

	float3 lig = float3(0.0f,0.0f,0.0f);		//ライト
	
	//シャドウ。
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	float shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);
	//float shadow = 0.0f;

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

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.xyz = float3(0.0f,1.0f,0.0f) * lig;
	finalColor.a = 1.0f;

	return finalColor;
}

//GBufferに書き込むピクセルシェーダーのエントリ関数。
PSOut_GBuffer PSMain_TerrainRenderGBuffer(SPSInTerrain psIn) {
	PSOut_GBuffer Out = (PSOut_GBuffer)0;

	Out.albedo = CalcTerrainTexture(psIn.uv, psIn.texType);		//アルベド。
	//法線マップ。
	Out.normal.xyz = (psIn.normal / 2.0f) + 0.5f;

	//ワールド座標。
	Out.worldPos = float4(psIn.worldPos, 0.0f);

	//スペキュラマップ。
	Out.specMap = 0.0f;

	//シャドウ。
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

	//反射率。
	Out.reflection = 0.0f;

	return Out;
}

//シャドウマップ描画用の頂点シェーダーの引数構造体。
struct SVSTerrainShadowIn {
	float4 pos : POSITION;
};
//シャドウマップ描画用のピクセルシェーダーの引数構造体。
struct SPSTerrainShadowIn {
	float4 pos : SV_POSITION;
};
/*
*	シャドウマップ書き込み用の頂点シェーダー。
*/
SPSTerrainShadowIn VSTerrainMainShadowMap(SVSTerrainShadowIn vsIn)
{
	SPSTerrainShadowIn psIn;

	psIn.pos = mul(mWorldShadow, vsIn.pos);
	psIn.pos = mul(mTerrainLVP, psIn.pos);

	return psIn;
}

/*
*	シャドウマップ書き込み用のピクセルシェーダー。
*/
float4 PSTerrainMainShadowMap(SPSTerrainShadowIn psIn) :SV_Target0
{
	return psIn.pos.z / psIn.pos.w;
}