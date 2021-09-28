#pragma once
#include "LightBase.h"
#include "graphics/light/LightData.h"

namespace Engine {
	namespace prefab {
		/// <summary>
		/// �|�C���g���C�g�B
		/// </summary>
		class CPointLight : public CLightBase
		{
		public:
			CPointLight();
			~CPointLight();
			bool StartSub()override final;		//���N���X��Start����Ăяo���B
			void Update()override final;		//�X�V�����B

		public:	//�Z�b�g�֐��B
			/// <summary>
			/// ���C�g�̍��W��ݒ�B
			/// </summary>
			void SetPoisition(const Vector3& pos)
			{
				m_light.position = pos;
			}
			/// <summary>
			/// ���C�g�̐F��ݒ�B
			/// </summary>
			void SetColor(const Vector3& color)
			{
				m_light.color = color;
			}
			/// <summary>
			/// �����p�����[�^��ݒ�B
			/// </summary>
			/// <param name="attn">
			/// �����萔�B
			/// <para>x�̓|�C���g���C�g�̉e�����͂��͈́B</para>
			/// <para>y�̓|�C���g���C�g�̌������ɉe����^����B</para>
			/// <para>y���傫���Ȃ�ƁA�����������Ȃ�A1.0�Ő��`�̌������ɂȂ�B</para>
			/// <para>z�͖��g�p�B</para>
			/// </param>
			void SetAttn(const Vector3& attn);

		public:	//�Q�b�g�֐��B
			/// <summary>
			/// ���C�g�̍��W���擾�B
			/// </summary>
			const Vector3& GetPosition()const
			{
				return m_light.position;
			}
			/// <summary>
			/// ���f�[�^�̎擾�B
			/// </summary>
			SPointLight& GetRawData()
			{
				return m_light;
			}
			/// <summary>
			/// ���̃��C�g���X�|�b�g���C�g�ɂ���B
			/// </summary>
			void EnableSpotLight()
			{
				m_light.hasDirection = 1;
			}
			/// <summary>
			/// �X�|�b�g���C�g�𖳌��ɂ���B
			/// </summary>
			void DisableSpotLight()
			{
				m_light.hasDirection = 0;
			}
			/// <summary>
			/// �X�|�b�g���C�g�̏Ǝ˕�����ݒ�B
			/// </summary>
			/// <param name="dir"></param>
			void SetSpotLightDirection(const Vector3& dir)
			{
				m_light.directionAndAngle.x = dir.x;
				m_light.directionAndAngle.y = dir.y;
				m_light.directionAndAngle.z = dir.z;
			}
			/// <summary>
			/// �X�|�b�g���C�g�̏Ǝˊp�x��ݒ�B
			/// </summary>
			/// <param name="rad">�Ǝˊp�x(�P��:���W�A��)</param>
			void SetSpotLightAngle(float rad)
			{
				m_light.directionAndAngle.w = rad;
			}
			/// <summary>
			/// �X�|�b�g���C�g�̏Ǝˊp�x��ݒ�B
			/// </summary>
			/// <param name="deg"></param>
			void SetSpotLightAngleDeg(float deg)
			{
				float rad = Math::DegToRad(deg);
				SetSpotLightAngle(rad);
			}

		private:
			SPointLight m_light;
		};
	}
}
