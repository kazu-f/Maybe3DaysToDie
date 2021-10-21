#pragma once
#include "Stage/IStage.h"
const int tableSize = 255;

class Hill:public IStage
{
public:
	Hill();
	~Hill() override final {}

	void OnDestroy();
	void CreateStage()override final;
	//高さをセットする
	void SetHeight(Vector3& pos);

private:
	//パーリンノイズ関数
	float PerlinNoize(float x,float y);

	//勾配ベクトルを求める
	Vector2 grad(int x, int y);

	void SetupRandomTable();

	float fade(float t);

	//float同士の線形補完関数
	float lerpf(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	
	//配列をシャッフルする
	void shuffle(int* array, int size);

private:
	const int MaxHeight = 1000;		// 最大の高さ
	const int Relief = 15;		//起伏の激しさ
	//シード値
	float SeedX = 0.0f;
	float SeedZ = 0.0f;
	const bool easeFlg = false;
	Vector2 randomTable[tableSize] = { Vector2::Zero };
	int permX[tableSize] = { 0 };
	int permY[tableSize] = { 0 };
};

