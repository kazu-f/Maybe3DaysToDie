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
float4 PSMain(SPSIn psIn) :SV_Target0
{
	//アルベド
	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);
	//半透明にする
	albedo.a = 0.75f;

	return albedo;
}