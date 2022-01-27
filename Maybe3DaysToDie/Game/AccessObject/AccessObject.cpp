#include "stdafx.h"
#include "AccessObject.h"
#include "RayTest.h"

void AccessObject::Access()
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
	//���C���Փ˂��Ă���Ƃ�
	if (callback.isHit)
	{
		m_hitObj = ((DestructibleObject*)callback.ColObj->getUserPointer());
		//�I�u�W�F�N�g��ID����K�؂ȃA�N�V�������N����
		auto& param = m_hitObj->GetParam();
		SwitchAction(m_SaveData->ObjectAccessTag[param.BlockID]);
	}

}

void AccessObject::SwitchAction(AccessTag tag)
{
	switch (tag)
	{
	case AccessTag::NonAccess:
		//�A�N�Z�X�s�̃I�u�W�F�N�g
		break;
	case AccessTag::Root:
		//���[�g�ł���I�u�W�F�N�g

		break;
	}
}