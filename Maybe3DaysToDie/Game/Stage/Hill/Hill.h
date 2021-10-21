#pragma once
#include "Stage/IStage.h"

class Hill:public IStage
{
public:
	Hill() {}
	~Hill() override final {}

	void OnDestroy();
	void CreateStage()override final;
	//高さをセットする
	void SetHeight(Vector3 pos);

private:
	//パーリンノイズ関数
	void PerlinNoize(float x,float y);

	//勾配ベクトルを求める
	Vector2 grad(int x, int y);
private:
	const int MaxHeight = 10;		// 最大の高さ
	const int Relief = 15;		//起伏の激しさ
	//シード値
	float SeedX = 0.0f;
	float SeedZ = 0.0f;
};

