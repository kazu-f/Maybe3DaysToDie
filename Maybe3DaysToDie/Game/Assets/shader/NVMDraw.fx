//頂点シェーダーへの入力頂点構造体。
struct VSInput{
	float4 pos : POSITION;
};
//頂点シェーダーの出力。
struct VSOutput{
	float4 pos : SV_POSITION;
};
//VP行列。
cbuffer VP : register(b0)
{
	float4x4 mrot;	//回転。
	float4x4 mview;	//ビュー。
	float4x4 mproj;	//プロジェ。
}	
//頂点シェーダー。
//１．引数は変換前の頂点情報。
//２．戻り値は変換後の頂点情報。
VSOutput VSMain(VSInput In) 
{
	VSOutput vsOut;
	//ビューとプロジェかけていく。
	In.pos = mul(In.pos, mrot);
	In.pos = mul(mview, In.pos);
	In.pos = mul(mproj, In.pos);
	//座標。
	vsOut.pos = In.pos;
   
	return vsOut;
}
//ピクセルシェーダー。
float4 PSMain(VSOutput vsOut) : SV_Target0
{
	return float4(0.0f, 1.0f, 0.0f, 1.0f);
}
//ワイヤーフレーム用ピクセルシェーダー。
float4 PSMainWire(VSOutput vsOut) : SV_Target0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}
//ライン用ピクセルシェーダー。
float4 PSMainLine(VSOutput vsOut) : SV_Target0
{
	return float4(0.0f, 0.0f,1.0f, 0.0f);
}

float4 PSMainLineRoot(VSOutput vsOut) : SV_Target0
{
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
}