/*
*	スカイキューブシェーダー。
*/

#include "modelCB.h"
#include "Fog.h"

TextureCube<float4> skyCubeMap : register(t0);		//スカイキューブマップ。

//サンプラステート。
sampler g_sampler : register(s0);

//頂点シェーダーへの入力。
struct SVSIn_SkyCube {
	float4 pos : POSITION;		//モデルの頂点座標。
	float3 normal : NORMAL;		//法線。
};

struct SPSIn_SkyCube {
	float4 pos : SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal : NORMAL;		//法線。
	float3 worldPos : TEXCODE0;	//ワールド座標。
};

//空用の頂点シェーダー。
SPSIn_SkyCube VSMain_SkyCube(SVSIn_SkyCube In) {
	SPSIn_SkyCube psIn;

	psIn.pos = mul(mWorld, In.pos);						//モデルの頂点をワールド座標系に変換。
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。
	//psIn.normal = In.normal;								//法線。
	psIn.normal = normalize(mul(mWorld, In.normal));		//法線をワールド座標系に変換。

	return psIn;
}

//空用のピクセルシェーダー。
float4 PSMain_SkyCube(SPSIn_SkyCube In) : SV_Target0
{
	float4 color;	
	color.xyz = skyCubeMap.Sample(g_sampler, In.normal).xyz;
	color.xyz += emissionColor;

	color = CalcSkyFog(color, In.worldPos.y);
	color.a = 1.0f;

	return color;
	//return float4(1.0f,0.0f,0.0f,1.0f);
}
