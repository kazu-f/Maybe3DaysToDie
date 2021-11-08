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
	//���_�̈ʒu
	Vector3 m_Start = MainCamera().GetPosition();
	//���������Ƀ|�W�V���������Z
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * SetRange;
	Vector3 cpos = MainCamera().GetPosition();
	Vector3 ctgt = MainCamera().GetTarget();
	Vector3 forward = cpos - ctgt;
	forward.Normalize();
	//���C�e�X�g�Ŏg�p����x�N�g�����쐬
	btVector3 start, end;
	start.setValue(m_Start.x, m_Start.y, m_Start.z);
	end.setValue(m_End.x, m_End.y, m_End.z);

	//���C�e�X�g
	RayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	//�ŏI�I�Ȉʒu
	Vector3 lastPos;
	lastPos.Set(end);
	//���C���Փ˂��Ă���Ƃ�
	if (callback.isHit)
	{
		lastPos = callback.hitColPos;
		//�n�`���擾
		auto terrain = FindGO<nsTerrain::TerrainWorld>("Terrain");
		//�c�[���̏����擾
		m_tool->GetInfo();
		//�n�`�Ƀ_���[�W��^����
		terrain->GetTerrain(lastPos).Damage(damage);
	}
}