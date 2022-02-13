
Texture2D<float4> shadowMap_0 : register(t6);		//シャドウマップ。
Texture2D<float4> shadowMap_1 : register(t7);		//シャドウマップ。
Texture2D<float4> shadowMap_2 : register(t8);		//シャドウマップ。

//シャドウマップの数
static const int NUM_SHADOW_MAP = 3;
/*
*	シャドウマップ用の定数バッファ。
*	ShadowMap.hのSShadowCbに対応する。
*/
cbuffer ShadowCb : register(b3) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//ライトビュープロジェクション行列。
	float4 texOffset[NUM_SHADOW_MAP];	//シャドウマップのサイズ。
	float4 depthOffset;	//深度オフセット。シャドウアクネ(チラつき)回避のためのバイアス。
										//値が大きいほど影が落ちにくくなる。
	float4 shadowAreaDepthInViewSpace;	//カメラ空間での影を落とすエリアの深度テーブル。
																		//なんか配列だと送れないんですが...
}
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
float CalcShadow(float3 worldPos, float zInView, int shadowReceiverFrag)
{
	float shadow = 0.0f;
	if (shadowReceiverFrag) {
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
