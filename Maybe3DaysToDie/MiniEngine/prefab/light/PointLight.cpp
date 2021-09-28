#include "MiniEngine.h"
#include "PointLight.h"

Engine::prefab::CPointLight::CPointLight()
{
}

Engine::prefab::CPointLight::~CPointLight()
{
}

bool Engine::prefab::CPointLight::StartSub()
{
	return true;
}

void Engine::prefab::CPointLight::Update()
{
	//�J������Ԃł̈ʒu���v�Z�B
	const Matrix& mView = MainCamera().GetViewMatrix();
	m_light.positionInView = m_light.position;
	mView.Apply(m_light.positionInView);
	//���C�g�̃}�e���A��ID�O���[�v��ݒ�B
	m_light.lightingMaterialIDGroup = GetLightingMaterialIDGroup();
}

void Engine::prefab::CPointLight::SetAttn(const Vector3& attn)
{
	m_light.attn = attn;
	if (m_light.attn.y <= 0.0f)
	{
		ENGINE_MESSAGE_BOX("attn.y�̒l���s���ł��B\n"
			"���̒l�͕K��0���傫���l��ݒ肷��K�v������܂��B");
		m_light.attn.y = 0.001f;
	}
}
