#include "stdafx.h"
#include "DirectionLight.h"

namespace Engine {
	namespace prefab {
		CDirectionLight::CDirectionLight()
		{
			m_light.color = Vector3::One;
			m_light.direction = Vector3::Down;
		}
		CDirectionLight::~CDirectionLight()
		{
		}
		bool CDirectionLight::StartSub()
		{
			return true;
		}
		void CDirectionLight::Update()
		{
			m_light.lightingMaterialIDGroup = GetLightingMaterialIDGroup();
		}
		void CDirectionLight::SetDirection(const Vector3& direction)
		{
			m_light.direction = direction;
			m_light.direction.Normalize();		//���K����̃x�N�g���������d���񂩂Ȃ��H
		}
		void CDirectionLight::SetColor(const Vector4& color)
		{
			m_light.color = color;
		}
	}

}