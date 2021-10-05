#include "stdafx.h"
#include "PlacementObject.h"

PlacementObject::PlacementObject()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);
}

PlacementObject::~PlacementObject()
{

}

void PlacementObject::OnDestroy()
{
	if (m_ObjectModel != nullptr)
	{
		DeleteGO(m_ObjectModel);
		m_ObjectModel = nullptr;
	}
}

bool PlacementObject::Start()
{
	ModelInitData m_modelInitData;
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	m_ObjectModel->Init(m_modelInitData);
	return true;
}

void PlacementObject::Update()
{
	//オブジェクトを設置する位置を計算
	CalcObjectPos();
	//各種セット
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);
}

void PlacementObject::CalcObjectPos()
{
	//視点の位置
	Vector3 m_Start = MainCamera().GetPosition();
	//視線方向にポジションを加算
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * m_SetRange;

	//レイテストで使用するベクトルを作成
	btVector3 start, end;
	start.setValue(m_Start.x, m_Start.y, m_Start.z);
	end.setValue(m_End.x, m_End.y, m_End.z);

	//レイテスト
	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);

	//最終的な位置
	Vector3 lastPos;
	lastPos.Set(end);

	//レイが衝突しているとき
	if (callback.isHit)
	{
		//当たった位置
		end = start + (end - start) * callback.m_closestHitFraction;
		lastPos.Set(end);

		//オブジェクトの間隔を100ごとにする
		int x, z;
		//小数点以下切り捨て
		x = static_cast<int>(lastPos.x);
		z = static_cast<int>(lastPos.z);

		//余りを求める
		int remain_x, remain_z;
		remain_x = x % 100;
		remain_z = z % 100;
		//四捨五入する
		float round_x, round_z;
		round_x = round(static_cast<float>(remain_x / 100.0f));
		round_z = round(static_cast<float>(remain_z / 100.0f));

		//単位戻す
		round_x *= 100.0f;
		round_z *= 100.0f;

		//ポジションに代入
		lastPos.x = static_cast<float>(x - remain_x);
		lastPos.z = static_cast<float>(z - remain_z);

		//四捨五入した値を加算
		lastPos.x += round_x;
		lastPos.z += round_z;
	}
	m_pos.Set(lastPos);
}