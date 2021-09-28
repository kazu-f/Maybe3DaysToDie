#pragma once

namespace Engine {
	namespace prefab {
		class CSpriteRender : public IGameObject
		{
		public:
			CSpriteRender() {};
			~CSpriteRender() {};
			/// <summary>
			/// �������B
			/// </summary>
			/// <param name="spriteData">�������f�[�^�B</param>
			/// <param name="isDraw3D">3D��Ԃŕ`�悷�邩�H</param>
			void Init(const SpriteInitData& spriteData, bool isDraw3D = false)
			{
				m_sprite.Init(spriteData,isDraw3D);	//�������B
				m_isDraw3D = isDraw3D;		//3D��Ԃŕ`�悷�邩�H
				m_isInited = true;			//�������ς݁B
			}
			/// <summary>
			/// �ȈՏ������B
			/// </summary>
			/// <param name="FilePath">�X�v���C�g�̃t�@�C���p�X�B</param>
			/// <param name="w">���B</param>
			/// <param name="h">�c�B</param>
			/// <param name="isDraw3D">3D��Ԃŕ`�悷�邩�H</param>
			void Init(const char* FilePath, float w, float h, bool isDraw3D = false);

		public:
			bool Start()override final;
			void Update()override final;
			void ForwardRender(RenderContext& rc)override final;
			void PostRender(RenderContext& rc)override final;
		public:		//Set�֐��B
			/// <summary>
			/// ���W��ݒ�B
			/// </summary>
			void SetPosition(const Vector3& pos)
			{
				m_position = pos;
			}
			/// <summary>
			/// ���W��ݒ�B(2D)
			/// </summary>
			void SetPosition(const Vector2& pos)
			{
				m_position.x = pos.x;
				m_position.y = pos.y;
			}
			/// <summary>
			/// ��]��ݒ�B
			/// </summary>
			void SetRotation(const Quaternion& rot)
			{
				m_rotation = rot;
			}
			/// <summary>
			/// �g�嗦��ݒ�B
			/// </summary>
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}
			/// <summary>
			/// �s�{�b�g��ݒ�B
			/// </summary>
			/// <param name="pivot">��_�B
			/// <para>{ 0.5, 0.5 }���摜�̒��S����_�B</para>
			/// <para>{ 0.0, 0.0 }�ŉ摜�̉E��B</para>
			/// <para>{ 1.0, 1.0 }�ŉ摜�̍����B</para>
			/// </param>
			void SetPivot(const Vector2& pivot)
			{
				m_pivot = pivot;
			}
			/// <summary>
			/// ��Z�J���[��ݒ�B
			/// </summary>
			void SetMulColor(const Vector4& mulColor)
			{
				m_sprite.SetMulColor(mulColor);
			}

		public:		//Get�֐��B
			/// <summary>
			/// ���W���擾�B
			/// </summary>
			const Vector3& GetPosition()const
			{
				return m_position;
			}
			/// <summary>
			/// ��]���擾�B
			/// </summary>
			const Quaternion& GetRotation()const
			{
				return m_rotation;
			}
			/// <summary>
			/// �g�嗦���擾�B
			/// </summary>
			const Vector3& GetScale()const
			{
				return m_scale;
			}

		private:
			Sprite m_sprite;								//�X�v���C�g�B
			Vector3 m_position = Vector3::Zero;				//���W�B
			Quaternion m_rotation = Quaternion::Identity;	//��]�B
			Vector3 m_scale = Vector3::One;					//�X�P�[���B
			Vector2 m_pivot = Sprite::DEFAULT_PIVOT;		//�s�{�b�g�B
			bool m_isInited = false;						//�������ς݁H
			bool m_isDraw3D = false;						//3D��Ԃŕ`�悷�邩�H
		};//class CSpriteRender;

	}//namespace prefab
}//namespace Engine
