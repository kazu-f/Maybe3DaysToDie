
//GBufferに書き込むための構造体。
struct PSOut_GBuffer {
	float4 albedo : SV_Target0;		//アルベドカラー。
	float4 normal : SV_Target1;		//法線。
	float4 worldPos : SV_Target2;	//ワールド座標。
	float4 specMap : SV_Target3;		//スペキュラ。
	float shadow : SV_Target4;		//シャドウ。
	float2 reflection : SV_Target5;	//反射率。
};
