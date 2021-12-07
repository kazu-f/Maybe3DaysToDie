#include "stdafx.h"
#include "Hill.h"
#include <random>

Hill::Hill()
{
	SetupRandomTable();
}

void Hill::OnDestroy()
{
	for (auto& ptr : m_model)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	for (auto& ptr : m_Terrain)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	//if (m_model != nullptr)
	//{
	//	DeleteGO(m_model);
	//	m_model = nullptr;
	//}
	//if (m_Terrain != nullptr)
	//{
	//	delete m_Terrain;
	//	m_Terrain = nullptr;
	//}
}

void Hill::CreateStage()
{
	//モデルの各種情報
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";

	//チャンクごとにマップを生成
	for (int Width = 0; Width < ChunkWidth; Width++)
	{
		for (int Depth = 0; Depth < ChunkWidth; Depth++)
		{
			prefab::ModelRender* m_ptr = NewGO<prefab::ModelRender>(0);
			m_ptr->Init(modelInitData);
			Vector3 pos = { 100.0f,-100.0f,100.0f };
			pos.x *= Width;
			pos.z *= Depth;
			SetHeight(pos);
			m_ptr->SetPosition(pos);
			//コライダーを作成
			CPhysicsStaticObject* col = nullptr;
			col = new CPhysicsStaticObject;
			col->CreateMesh(pos, Quaternion::Identity, Vector3::One, m_ptr);
			//メモリ確保
			nsTerrain::Terrain* t_ptr = new nsTerrain::Terrain();
			//コライダーの作成
			//t_ptr->CreateCollider(m_ptr);
			//配列に追加
			m_model.push_back(std::move(m_ptr));
			m_Terrain.push_back(std::move(t_ptr));
		}
	}

	////モデルをnew
	//m_model = NewGO<prefab::ModelRender>(0);
	////モデルの各種情報
	//ModelInitData modelInitData;
	//modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	////モデルを初期化
	//m_model->Init(modelInitData, nullptr, 0, ChunkWidth * ChunkDepth);

	////チャンクごとにマップを生成
	//for (int Width = 0; Width < ChunkWidth; Width++)
	//{
	//	for (int Depth = 0; Depth < ChunkDepth; Depth++)
	//	{
	//		Vector3 pos = { 100.0f,0.0f,100.0f };
	//		pos.x *= Width;
	//		pos.z *= Depth;
	//		SetHeight(pos);
	//		m_model->UpdateInstancingData(pos, Quaternion::Identity, Vector3::One);
	//		//コライダーを作成
	//		m_StaticCol[Width][Depth].CreateMesh(pos, Quaternion::Identity, Vector3::One, m_model);
	//	}
	//}
	//m_Terrain = new nsTerrain::Terrain;
	//m_Terrain->SetModel(m_model);
}

void Hill::SetHeight(Vector3& pos)
{
	//パーリンノイズで使う値を求める
	int y = static_cast<int>(pos.y);
	float xSample = (pos.x + SeedX) / Relief;
	float zSample = (pos.z + SeedZ) / Relief;
	//ノイズをパーリンノイズで出した値にする
	float noise = PerlinNoize(xSample, zSample);
	y = MaxHeight * noise;		//高さを最大値*noiseにする
	y = static_cast<int>(y);
	//10の位の余りを求める
	float roundY = y % 100;
	//yを100ごとにする
	y -= roundY;
	//四捨五入
	roundY /= 100.0f;
	roundY = round(roundY);
	roundY *= 100.0f;
	//yに加算
	y += roundY;
	pos.y = static_cast<float>(y);
}

float Hill::PerlinNoize(float x,float y)
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
	//左上
	Vector2 g00 = grad(xi, yi);
	Vector2 s00 = { xf,yf };
	float f00 = g00.Dot(s00);
	//右上
	Vector2 g10 = grad(xi + 1.0f, yi);
	Vector2 s10 = { xf - 1.0f,yf };
	float f10 = g10.Dot(s10);
	//左下
	Vector2 g01 = grad(xi, yi + 1.0f);
	Vector2 s01 = { xf, yf - 1.0f };
	float f01 = g01.Dot(s01);
	//右下
	Vector2 g11 = grad(xi + 1.0f, yi + 1.0f);
	Vector2 s11 = { xf - 1.0f,yf - 1.0f };
	float f11 = g11.Dot(s11);

	//より自然な変化を見せるための補正
	float ux = fade(xf) * 1.0f;
	float uy = fade(yf) * 1.0f;

	//上側の2点(00,10)と下側の2点(01,11)それぞれでの影響の平均値
	float f0010 = lerpf(f00, f10, ux);
	float f0111 = lerpf(f01, f11, ux);
	//最終的な周囲の4点からの影響値の平均
	float fAve = lerpf(f0010, f0111, uy);

	return (fAve + 1.0f) / 2.0f;
}

void Hill::SetupRandomTable()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(-1.0, 1.0);
	//ランダムテーブル生成
	for (int i = 0; i < tableSize; i++)
	{
		float rx = distr(eng);
		float ry = distr(eng);
		Vector2 v1 = { rx,ry };
		Vector2 v2 = { 1.0f,1.0f };
		//-1.0 ～ 1.0
		v1 = v1 * 2.0f;
		v1 = v1 - v2;
		randomTable[i] = v1;
	}
	for (int j = 0; j < tableSize; j++)
	{
		permX[j] = j;
		permY[j] = j;
	}
	//配列をシャッフルする
	shuffle(permX, tableSize);
	shuffle(permY, tableSize);
}

Vector2 Hill::grad(int x, int y)
{
	int pX = permX[int(x % tableSize)];
	int pY = permY[int((y + pX) % tableSize)];
	Vector2 returnVec = { randomTable[pY].x,randomTable[pY].y };
	return returnVec;
}

float Hill::fade(float t)
{
	if (easeFlg)
	{
		//6t^5 - 15t^4 + 10t^3
		return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
	}
	else
	{
		//3t^2 - 2t^3
		return t * t * (3.0f - 2.0f * t);
	}
}

void Hill::shuffle(int* array, int size)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	for (int i = 0; i < size; i++)
	{
		//i～sizeのランダムなintを生成
		std::uniform_int_distribution<> distr(i,size);
		int r = distr(eng);
		int tmp = array[i];
		array[i] = array[r];
		array[r] = tmp;
	}
}