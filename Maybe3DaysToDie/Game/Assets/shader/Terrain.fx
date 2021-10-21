
//地形用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mView			: packoffset(c0);
	float4x4 mProj			: packoffset(c4);
};

//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos : POSITION;		//地形の頂点座標。
};

struct SPSIn {
	float4 pos : SV_POSITION;	//スクリーン空間でのピクセルの座標。
};


/// <summary>
/// 地形用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psIn;

	psIn.pos = mul(mView, vsIn.pos);						//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);						//カメラ座標系からスクリーン座標系に変換。

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{

	return float4(1.0f,0.0f,0.0f,1.0f);
}

