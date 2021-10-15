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
	m_modelInitData.m_shaderData.vsFxFilePath = L"Assets/shader/model.fx";
	m_modelInitData.m_shaderData.vsEntryPointFunc = "VSMain";
	m_modelInitData.m_shaderData.psFxFilePath = L"Assets/shader/ObjectPreview.fx";
	m_modelInitData.m_shaderData.psEntryPointFunc = "PSMain";
	m_ObjectModel->Init(m_modelInitData);
	m_ObjectModel->SetForwardRenderFlag(true);
	m_ObjectModel->SetShadowCasterFlag(true);
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

	//if (Pad(0).IsTrigger(enButtonA))
	//{
	//	PlaceObject();
	//}
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
		int x, y,z;
		//小数点以下切り捨て
		x = static_cast<int>(lastPos.x);
		y = static_cast<int>(lastPos.y);
		z = static_cast<int>(lastPos.z);

		//余りを求める
		int remain_x, remain_y, remain_z;
		remain_x = x % 100;
		remain_y = y % 100;
		remain_z = z % 100;

		//四捨五入する
		//高さはそのまま切り捨て
		float round_x, round_z;
		round_x = round(static_cast<float>(remain_x / 100.0f));
		round_z = round(static_cast<float>(remain_z / 100.0f));

		//単位戻す
		round_x *= 100.0f;
		round_z *= 100.0f;

		//ポジションに代入
		lastPos.x = static_cast<float>(x - remain_x);
		//lastPos.y = static_cast<float>(y - remain_y);
		lastPos.z = static_cast<float>(z - remain_z);

		//四捨五入した値を加算
		lastPos.x += round_x;
		lastPos.z += round_z;

		////上方向と衝突点の法線のなす角度を求める。
		//float angle = callback.hitNormal.Dot(Vector3::Up);
		////角度を変換
		//angle = fabsf(acosf(angle));
		////地面にあたっている
		//if (angle < Math::PI * 0.3f)
		//{
		//	//四捨五入する
		//	float round_y = round(static_cast<float>(remain_y / 100.0f));
		//	//加算
		//	lastPos.y += round_y;
		//}
	}
	m_pos.Set(lastPos);
}

//todo [最適化]後で処理見直せ
void PlacementObject::PlaceObject()
{
	//初期化
	ModelInitData m_modelInitData;
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	prefab::ModelRender* m_object = NewGO<prefab::ModelRender>(0);
	m_object->Init(m_modelInitData);
	//ポジションをセット
	m_object->SetPosition(m_pos);
	//配列に追加
	m_model.push_back(std::move(m_object));
	CPhysicsStaticObject* col; 
	col = new CPhysicsStaticObject;
	col->CreateMesh(m_pos, m_qrot, m_scale, m_object);
	m_col.push_back(col);
}