#pragma once

/// <summary>
/// グラフィックに関する設定。
/// </summary>

namespace Engine {

	/// <summary>
	/// シャドウマップのコンフィグ。
	/// </summary>

	static const int NUM_SHADOW_MAP = 3;		//シャドウマップの数。

	struct SShadowMapConfig
	{
		bool 	isEnable = true;				//影を落とす処理が有効かどうかのフラグ。
		int		shadowMapWidth = 4096;			//シャドウマップの幅。
		int		shadowMapHeight = 4096;			//シャドウマップの高さ。
		float	lightHeight = 1000.0f;			//ライトの高さ。
		float	depthOffset[NUM_SHADOW_MAP] = { 0.0002f , 0.0002f , 0.0002f };	//!<シャドウオフセット。この値を大きくすると、影が落ちにくくなる。
		float	shadowAreas[NUM_SHADOW_MAP] = { 2000.0f ,4000.0f , 20000.0f };			//影が落ちる範囲。
		//float	offsetTexelWorld = 0.05f;			//!<ブラーの時にフェッチするオフセット座標。ワールド空間の量。値が大きいほど大きくボケる。
	};

	struct STonemapConfig {
		bool isEnable = false;
		float luminance = 0.34f;		//明るさ。値が大きいほど明るくなる。
	};

	struct SPostEffectConfig
	{
		STonemapConfig tonemap;					//トーンマップの設定。
		bool isBloom = true;					//ブルームを有効にするか？
		bool isFxaa = true;						//アンチエイリアスを有効にするか？
	};

	struct SGraphicsConfig
	{
		SShadowMapConfig shadowConf;
		SPostEffectConfig postEffectConf;
	};

}