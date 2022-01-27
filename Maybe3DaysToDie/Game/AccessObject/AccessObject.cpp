#include "stdafx.h"
#include "AccessObject.h"
#include "RayTest.h"

void AccessObject::Access()
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
	//レイが衝突しているとき
	if (callback.isHit)
	{
		m_hitObj = ((DestructibleObject*)callback.ColObj->getUserPointer());
		//オブジェクトのIDから適切なアクションを起こす
		auto& param = m_hitObj->GetParam();
		SwitchAction(m_SaveData->ObjectAccessTag[param.BlockID]);
	}

}

void AccessObject::SwitchAction(AccessTag tag)
{
	switch (tag)
	{
	case AccessTag::NonAccess:
		//アクセス不可のオブジェクト
		break;
	case AccessTag::Root:
		//ルートできるオブジェクト

		break;
	}
}