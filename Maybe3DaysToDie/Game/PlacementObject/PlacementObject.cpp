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
	//�I�u�W�F�N�g��ݒu����ʒu���v�Z
	CalcObjectPos();
	//�e��Z�b�g
	m_ObjectModel->SetPosition(m_pos);
	m_ObjectModel->SetRotation(m_qrot);
	m_ObjectModel->SetScale(m_scale);
}

void PlacementObject::CalcObjectPos()
{
	//���_�̈ʒu
	Vector3 m_Start = MainCamera().GetPosition();
	//���������Ƀ|�W�V���������Z
	Vector3 m_End = m_Start;
	m_End += MainCamera().GetForward() * m_SetRange;

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
		//���������ʒu
		end = start + (end - start) * callback.m_closestHitFraction;
		lastPos.Set(end);

		//�I�u�W�F�N�g�̊Ԋu��100���Ƃɂ���
		int x, z;
		//�����_�ȉ��؂�̂�
		x = static_cast<int>(lastPos.x);
		z = static_cast<int>(lastPos.z);

		//�]������߂�
		int remain_x, remain_z;
		remain_x = x % 100;
		remain_z = z % 100;
		//�l�̌ܓ�����
		float round_x, round_z;
		round_x = round(static_cast<float>(remain_x / 100.0f));
		round_z = round(static_cast<float>(remain_z / 100.0f));

		//�P�ʖ߂�
		round_x *= 100.0f;
		round_z *= 100.0f;

		//�|�W�V�����ɑ��
		lastPos.x = static_cast<float>(x - remain_x);
		lastPos.z = static_cast<float>(z - remain_z);

		//�l�̌ܓ������l�����Z
		lastPos.x += round_x;
		lastPos.z += round_z;
	}
	m_pos.Set(lastPos);
}