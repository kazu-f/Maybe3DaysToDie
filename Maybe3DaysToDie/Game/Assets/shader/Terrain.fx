
//地形用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mView			: packoffset(c0);
	float4x4 mProj			: packoffset(c4);
};

//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos : POSITION;		//地形の頂点座標。
	float2 uv : TEXCOORD0;	//UV座標。
};

struct SPSIn {
	float4 pos : SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv : TEXCOORD0;	//UV座標。
};

Texture2D<float4> g_albedoMap : register(t0);	//アルベド

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
	psIn.uv = vsIn.uv;

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//アルベド。
	albedoColor.a = 1.0f;

	return albedoColor;
}

