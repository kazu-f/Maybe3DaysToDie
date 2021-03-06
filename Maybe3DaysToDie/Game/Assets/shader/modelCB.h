

//モデル用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mWorld			: packoffset(c0);
	float4x4 mView			: packoffset(c4);
	float4x4 mProj			: packoffset(c8);
	float3 emissionColor	: packoffset(c12);			//自己発光光。
	int isShadowReceiver	: packoffset(c12.w);		//シャドウレシーバー。
};

/*
*	ライト用の定数バッファ
*	tkLightManager.hのSLightParamと対応する。
*/
cbuffer lightCb : register(b1)
{
	float3 eyePos			: packoffset(c0);		//カメラの位置。
	int numDirectionLight	: packoffset(c0.w);		//ディレクションライトの数。
	float3 ambientLight		: packoffset(c1);		//アンビエントライト。
	int numPointLight		: packoffset(c1.w);		//ポイントライトの数。
	float4 screenParam		: packoffset(c2);		//スクリーンパラメータ(neae,far,screenW,screenH)
}

/*
*	マテリアルの定数バッファ
*	Material.hのSMaterialParamに対応する。
*/
cbuffer MaterialParamCb : register(b2) {
	int hasNormalMap		: packoffset(c0.x);		//法線マップがある？
	int hasSpecularMap		: packoffset(c0.y);		//スペキュラマップがある？
	int hasReflectionMap	: packoffset(c0.z);		//反射マップがある？
}
