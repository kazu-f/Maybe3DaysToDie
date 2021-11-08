#include "stdafx.h"
#include "DestroyObject.h"
#include "TerrainManager/TerrainWorld.h"
#include "Tool/Tool.h"

DestroyObject::DestroyObject()
{

}

DestroyObject::~DestroyObject()
{

}

void DestroyObject::Update()
{
	if (Pad(0).IsTrigger(enButtonB))
	{
		AddObjectDamage(100);
	}
}

void DestroyObject::AddObjectDamage(int damage)
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
	//レイが衝突しているとき
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		//地形を取得
		auto terrain = FindGO<nsTerrain::TerrainWorld>("Terrain");
		//ツールの情報を取得
		m_tool->GetInfo();
		//地形にダメージを与える
		terrain->GetTerrain(lastPos).Damage(damage);
	}
}