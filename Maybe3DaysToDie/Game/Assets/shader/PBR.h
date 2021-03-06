
//円周率。
static const float PI = 3.14159265358979323846;

//ベックマン分布?	
//光の分散具合を求める？
/*
	m			(面の粗さ)
	t = N・H	(法線・ハーフベクトル)
	M = m^2		T = (N・H)^2
*/
float Beckmann(float m, float t)
{

	float t2 = t * t;
	float t4 = t * t * t * t;
	float m2 = m * m;
	float D = 1.0f / (4.0f * m2 * t4);
	D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
	return D;

	//float M = m;
	//float T = t * t;
	//return exp((T - 1) / (M * T)) / (PI * M * T * T);
}

//フレネル項?の近似式らしい？
float specFresnel(float f0, float u)
{
	//金属反射のためf90は1.0固定でいい。
	return f0 + (1.0f - f0) * pow(1.0f - u, 5);
}

/*
*	クックトランスモデルの鏡面反射を計算。
*	スペキュラの計算に使ってる。？
*	Lがライト
*	Vが視点
*	Nが法線
*/
float CookTrranceSpecular(float3 L, float3 V, float3 N, float metaric)
{
	float microfacet = max(0.18f, 1.0f - metaric);		//マイクロファセット
									//表面の凸凹具合を表す的な？
									//面の粗さとかを調整するパラメータらしい？
	float f0 = metaric;				//垂直入射時のフレネル反射係数。

	float3 H = normalize(L + V);		//ライト+視点のハーフベクトル。

	//色々内積取ってる。
	float NdotH = saturate(dot(N, H));		//法線とハーフベクトル
	float VdotH = saturate(dot(V, H));		//視点とハーフベクトル
	float NdotL = saturate(dot(N, L));		//法線とライト
	float NdotV = saturate(dot(N, V));		//法線と視点

	float D = Beckmann(microfacet, NdotH);	//微小面分布関数。
	float F = specFresnel(f0, VdotH);		//フレネル項。

	float t = 2.0 * NdotH / VdotH;			//計算の共通項を取っておく感じ。
	float G = min(1.0f, min(t * NdotV, t * NdotL));		//幾何学的減衰係数？
																	//最大値を1.0、最小値を0.0の間で
																	//値の小さいほうを取る

	float m = PI * max(NdotV * NdotL,0.01f);			//クックトランス反射モデルの分母になる値？	

	/*
	*	F:フレネル項
	*	D:微小面分布
	*	G:幾何学的減衰係数
	*/
	return max(F * D * G / m, 0.0f);
}

/*
*	フレネル式の近似式。
*	f0が垂直に光が入射したときのフレネル反射率。
*	f90が平行に光が入射したときのフレネル反射率。
*/
float SchlickFresnel(float u, float f0, float f90)
{
	return f0 + (f90 - f0) * pow(1.0f - u, 5.0f);
}

/*
*	正規化Disneyモデル拡散反射。
*	albedColor	:	ライトの強さか？
*	N			:	法線の正規化ベクトル
*	L			:	ライトへの正規化ベクトル
*	V			:	視点の正規化ベクトル
*	roughness	:	表面の粗さを表すパラメータらしい
*/
float NormalizedDisneyDiffuse(float3 N, float3 L, float3 V, float roughness)
{
	////法線とライト方向の内積。
	//float dotNL = saturate(dot(N, L));
	////法線と視点方向の内積。
	//float dotNV = saturate(dot(N, V));

	//return max(0.2f, dotNL * dotNV);

	float3 H = normalize(L + V);		//ハーフベクトル。

	float energyBias = lerp(0.0f, 0.5f, roughness);				//なんか正規化のための数値？0.0〜0.5の線形補完
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
	//内積する。(下限0.0〜上限1.0)
	float LdotH = saturate(dot(L, H));		//ライトとハーフベクトル
	float NdotL = saturate(dot(N, L));		//法線とライト
	float NdotV = saturate(dot(N, V));		//法線と視点
	float HdotV = saturate(dot(H, V));		//ハーフベクトルと視点

	//謎数値　フレネル反射率?(0.0〜1.0)
	//光が平行に入射したときのフレネル反射率を求める。
	float Fd90 = energyBias + 2.0f * LdotH * LdotH * roughness;

	float FL = SchlickFresnel(NdotL, 1.0f, Fd90);	//フレネル係数(法線・ライト)
	float FV = SchlickFresnel(NdotV, 1.0f, Fd90);	//フレネル係数(法線・視点)

	/*
	*	フレネル係数(N・L) * フレネル係数(N・V)
	*	これを正規化ランバート拡散へ掛ける。
	*/
	return (FL * FV * energyFactor);
}