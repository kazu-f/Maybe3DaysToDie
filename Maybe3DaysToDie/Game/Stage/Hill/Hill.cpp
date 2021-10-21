#include "stdafx.h"
#include "Hill.h"

void Hill::OnDestroy()
{
	if (m_model != nullptr)
	{
		DeleteGO(m_model);
		m_model = nullptr;
	}
	if (m_Terrain != nullptr)
	{
		delete m_Terrain;
		m_Terrain = nullptr;
	}
}

void Hill::CreateStage()
{
	//モデルをnew
	m_model = NewGO<prefab::ModelRender>(0);
	//モデルの各種情報
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	//モデルを初期化
	m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	//チャンクごとにマップを生成
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkDepth; Depth++)
		{
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
			//コライダーを作成
			m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
		}
	}
	m_Terrain = new nsTerrain::Terrain;
	m_Terrain->SetModel(m_model);
}

void Hill::SetHeight(Vector3 pos)
{
	//パーリンノイズで使う値を求める
	float y = 0.0f; // yを0にする
	float xSample = (pos.x + SeedX) / Relief;
	float zSample = (pos.z + SeedZ) / Relief;
	//ノイズをパーリンノイズで出した値にする
}

void Hill::PerlinNoize(float x,float y)
{
	//切り捨てて整数にする
	int xi = static_cast<int>(x);
	int yi = static_cast<int>(y);

	//左下の座標からの距離
	float xf = (x - xi);
	float yf = (y - yi);

	//周囲の4つの座標ごとの影響値を勾配ベクトルと距離ベクトルの内積で求める
	//gXX 各点の勾配ベクトル
	//sXX 各点から今見ている座標を指すベクトル
	//vXX gXXとsXXの内積
	Vector2 g00 = grad(xi, yi);
	Vector2 s00 = { xf,yf };
	float v00 = g00.Dot(s00);
}

Vector2 Hill::grad(int x, int y)
{

}