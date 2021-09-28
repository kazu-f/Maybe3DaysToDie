#pragma once
#include "LightBase.h"
#include "graphics/light/LightData.h"

namespace Engine {
	namespace prefab {
		/// <summary>
		/// �f�B���N�V�������C�g�B
		/// </summary>
		class CDirectionLight : public CLightBase
		{
		public:
			CDirectionLight();
			~CDirectionLight();
			bool StartSub()override final;
			void Update()override final;
			/// <summary>
			/// ���C�g�̕�����ݒ�B
			/// </summary>
			void SetDirection(const Vector3& direction);
			/// <summary>
			/// �f�B���N�V�������C�g�̕������擾�B
			/// </summary>
			const Vector3& GetDirection()const
			{
				return m_light.direction;
			}
			/// <summary>
			/// ���C�g�̃J���[��ݒ�B
			/// </summary>
			/// <param name="color">���C�g�̃J���[�B</param>
			void SetColor(const Vector4& color);
			/// <summary>
			/// ���C�g�̃J���[���擾
			/// </summary>
			const Vector4& GetColor()const
			{
				return m_light.color;
			}
			/// <summary>
			/// ���f�[�^�̎擾�B
			/// </summary>
			SDirectionLight& GetRawData()
			{
				return m_light;
			}

		private:
			SDirectionLight m_light;		//!<���C�g�̃f�[�^�B

		};//// class CDirectionLight
	}
}

