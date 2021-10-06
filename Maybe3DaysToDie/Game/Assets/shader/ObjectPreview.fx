#include "modelStruct.h"
#include "modelCB.h"
#include "CalcShadow.h"

//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);

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

	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);		//アルベド。
	Out.albedo = albedo;
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