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
	//�I�u�W�F�N�g��ݒu����ʒu���v�Z
	CalcObjectPos();
	//�e��Z�b�g
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
		int x, y,z;
		//�����_�ȉ��؂�̂�
		x = static_cast<int>(lastPos.x);
		y = static_cast<int>(lastPos.y);
		z = static_cast<int>(lastPos.z);

		//�]������߂�
		int remain_x, remain_y, remain_z;
		remain_x = x % 100;
		remain_y = y % 100;
		remain_z = z % 100;

		//�l�̌ܓ�����
		//�����͂��̂܂ܐ؂�̂�
		float round_x, round_z;
		round_x = round(static_cast<float>(remain_x / 100.0f));
		round_z = round(static_cast<float>(remain_z / 100.0f));

		//�P�ʖ߂�
		round_x *= 100.0f;
		round_z *= 100.0f;

		//�|�W�V�����ɑ��
		lastPos.x = static_cast<float>(x - remain_x);
		//lastPos.y = static_cast<float>(y - remain_y);
		lastPos.z = static_cast<float>(z - remain_z);

		//�l�̌ܓ������l�����Z
		lastPos.x += round_x;
		lastPos.z += round_z;

		////������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
		//float angle = callback.hitNormal.Dot(Vector3::Up);
		////�p�x��ϊ�
		//angle = fabsf(acosf(angle));
		////�n�ʂɂ������Ă���
		//if (angle < Math::PI * 0.3f)
		//{
		//	//�l�̌ܓ�����
		//	float round_y = round(static_cast<float>(remain_y / 100.0f));
		//	//���Z
		//	lastPos.y += round_y;
		//}
	}
	m_pos.Set(lastPos);
}

//todo [�œK��]��ŏ���������
void PlacementObject::PlaceObject()
{
	//������
	ModelInitData m_modelInitData;
	m_modelInitData.m_tkmFilePath = "Assets/modelData/CubeBlock/woodBlock.tkm";
	prefab::ModelRender* m_object = NewGO<prefab::ModelRender>(0);
	m_object->Init(m_modelInitData);
	//�|�W�V�������Z�b�g
	m_object->SetPosition(m_pos);
	//�z��ɒǉ�
	m_model.push_back(std::move(m_object));
	CPhysicsStaticObject* col; 
	col = new CPhysicsStaticObject;
	col->CreateMesh(m_pos, m_qrot, m_scale, m_object);
	m_col.push_back(col);
}