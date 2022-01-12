#include "stdafx.h"
#include "PlacementObject.h"
#include "Block/BlockManager/BlockManager.h"

PlacementObject::PlacementObject()
{
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
	for (auto model : m_model)
	{
		delete model;
	}
}

bool PlacementObject::Start()
{
	m_ObjectModel = NewGO<prefab::ModelRender>(0);

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

	if (Pad(0).IsTrigger(enButtonA))
	{
		//パラメータ
		ObjectParams param;
		param.Durable = 500;
		auto name = "Assets/modelData/CubeBlock/woodBlock.tkm";
		param.BlockName = name;
		PlaceObject(param);
	}
}

void PlacementObject::CalcObjectPos()
{
	//視点の位置
	Vector3 m_Start = MainCamera().GetPosition();
	//視線方向にポジションを加算
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * SetRange;
	Vector3 cpos = MainCamera().GetPosition();
	Vector3 ctgt = MainCamera().GetTarget();
	Vector3 forward = cpos - ctgt;
	forward.Normalize();
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
	CanPlace = callback.isHit;
	//レイが衝突しているとき
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		lastPos += callback.hitNormal * 100.0f;
	}
	m_pos.Set(lastPos);
}

//todo [最適化]後で処理見直せ
void PlacementObject::PlaceObject(ObjectParams& params)
{
	if (CanPlace)
	{
		Quaternion rot = Quaternion::Identity;
		Vector3 scale = Vector3::One;
		m_BlockManager->AddBlock(params, m_pos, rot, scale);
	}
}