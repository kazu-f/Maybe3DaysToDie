#include "stdafx.h"
#include "AccessObject.h"
#include "RayTest.h"
#include "Item/ItemDataFile.h"
#include "Item/GameItemPlaceObj.h"

AccessObject::AccessObject()
{
	Init();
}

AccessObject::~AccessObject()
{
	OnDestroy();
}

void AccessObject::Init()
{
	m_BoxSprite = NewGO<prefab::CSpriteRender>(2);
	SpriteInitData initData;
	initData.m_ddsFilePath[0] = "Assets/sprite/Root.dds";
	initData.m_fxFilePath = "Assets/shader/sprite.fx";
	initData.m_width = FRAME_BUFFER_H;
	initData.m_height = FRAME_BUFFER_H;
	//スプライトを初期化
	m_BoxSprite->Init(initData);
	m_BoxSprite->SetPosition(Vector2::Zero);
	m_BoxSprite->SetActiveFlag(IsSpriteActive);
}

void AccessObject::OnDestroy()
{
	DeleteGO(m_BoxSprite);
}

void AccessObject::Access()
{
	if (IsSpriteActive)
	{
		//既にアクセス中です。
		return;
	}
	//視点の位置
	Vector3 m_Start = MainCamera().GetPosition();
	//視線方向にポジションを加算
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * PlayerRange * OBJECT_UNIT;
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
		auto* placeObj = ItemDataFile::GetInstance()->GetPlaceData(param.BlockID);
		if (placeObj == nullptr)
		{
			return;
		}
		SwitchAction(placeObj->GetAccessTag(), param.BlockID);
	}

}

void AccessObject::SwitchAction(AccessTag tag,int id)
{
	switch (tag)
	{
	case AccessTag::NonAccess:
		//アクセス不可のオブジェクト
		break;
	case AccessTag::Root:
		//ルートできるオブジェクト
		//スプライト表示
		SwitchSpriteActive();
		m_Chest.Root(id);
		break;
	}
}