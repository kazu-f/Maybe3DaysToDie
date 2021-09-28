#pragma once

namespace Engine {
	namespace prefab {
		/// <summary>
		/// ���`�悷��Q�[���I�u�W�F�N�g�B
		/// </summary>
		/// <remarks>
		/// CubuMap�𗘗p������̕`����s���B���𑜓x�̋�̕`�悪�s����B
		/// </remarks>
		class CSky :public IGameObject
		{
		public:
			/// <summary>
			/// �R���X�g���N�^�B
			/// </summary>
			CSky();
			/// <summary>
			/// �f�X�g���N�^�B
			/// </summary>
			~CSky();
			/// <summary>
			/// �J�n�����B
			/// </summary>
			bool Start() override final;
			/// <summary>
			/// �X�V�����B
			/// </summary>
			void Update() override final;
			/// <summary>
			/// �폜�������B
			/// </summary>
			void OnDestroy() override final;

		public:
			Texture& GetSkyCubeMap()
			{
				return m_skyCube;
			}

		public:		//Set�֐��B
			//��̃T�C�Y��ݒ�B�P��:m
			void SetScale(float scale) 
			{
				m_scale = { scale,scale,scale };
				m_isDirty = true;
			}
			//��̃T�C�Y��ݒ�(�x�N�g��)�B�P��:m
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
				m_isDirty = true;
			}
			//���Ȕ����J���[��ݒ�B
			void SetEmissionColor(const Vector3& emissionColor)
			{
				m_emissionColor = emissionColor;
				m_isDirty = true;
			}
			//��̈ʒu��ݒ�B
			void SetPosition(const Vector3& pos)
			{
				m_position = pos;
				m_isDirty = true;
			}
			/// <summary>
			/// ��̃L���[�u�}�b�v�̃t�@�C���p�X��ݒ�B
			/// </summary>
			/// <param name="filepath">�t�@�C���p�X�B</param>
			/// <remarks>
			/// �C�ӂ̃L���[�u�}�b�v�ɕύX�������ꍇ�ɁA�g�p����B
			/// �ύX���Ȃ���΁A�f�t�H���g�̃L���[�u�}�b�v�����[�h�����B
			/// ���̊֐��𗘗p����ꍇ�́A�C���X�^���X�쐬����ɗ��p����B
			/// ����ȊO�̃^�C�~���O�ł́A���ɃL���[�u�}�b�v�����[�h�ς݂ƂȂ�A
			/// �ύX���ł��Ȃ��B
			/// </remarks>
			/// <example>
			/// �L���[�u�}�b�v��ύX����T���v���R�[�h�B
			/// </example>
			/// <code>
			/// auto sky = NewGO<prefab::CSky>(0);		//��̃C���X�^���X���쐬�B
			/// sky->SetSkyCubeMapFilePath("hoge.dds");	//�L���[�u�}�b�v�����ւ��B
			/// </code>
			void SetSkyCubeMapFilePath(const wchar_t filePath)
			{
#ifdef _DEBUG
				if (m_isStart == true) {
					ENGINE_WARNING_LOG("SkyCubeMap�̃��[�h���������Ă��邽��"
					"�L���[�u�}�b�v�̍����ւ��͂ł��܂���B"
					"�K�؂ȃ^�C�~���O�Ŋ֐��𗘗p���Ă��������B")
				}
#endif
				m_skyCubeMapFilePath = filePath;
			}
			/// <summary>
			/// ��̃��f���̃t�@�C���p�X��ݒ�B
			/// </summary>
			/// <param name="filePath">�t�@�C���p�X�B</param>
			/// <remarks>
			/// �C�ӂ̋�̃��f���ɕύX�������ꍇ�Ɏg�p����B
			/// �ύX���Ȃ���΁A�f�t�H���g�̋�̃��f�������[�h�����B
			/// �֐��𗘗p����ꍇ�́A�C���X�^���X���쐬��������ɗ��p����B
			/// ����ȊO�̃^�C�~���O�ł́A���ɋ�̃��f�������[�h�ς݂ƂȂ�A
			/// �ύX���邱�Ƃ��ł��Ȃ��B
			/// </remarks>
			/// <example>
			/// ���f����ύX����T���v���R�[�h�B
			/// </example>
			/// <code>
			/// auto sky = NewGO<prefab::CSky>(0);
			/// sky->SetSkyModelFilePath("hoge.tkm");
			/// </code>
			void SetSkyModelFilePath(const char* filePath) 
			{
#ifdef _DEBUG
				if (m_isStart == true) {
					ENGINE_WARNING_LOG("��̃��f���̃��[�h���������Ă��邽��"
						"��̃��f���̍����ւ��͂ł��܂���B"
						"�K�؂ȃ^�C�~���O�Ŋ֐��𗘗p���Ă��������B");
				}
#endif
				m_skyModelFilePath = filePath;
			}
		private:
			prefab::ModelRender* m_modelRender = nullptr;			//���f���`��̃Q�[���I�u�W�F�N�g�B
			Texture m_skyCube;										//�X�J�C�L���[�u�}�b�v��SRV�B
			Vector3 m_scale = { 100.0f,100.0f,100.0f };				//��̊g�嗦�B(�P��:m)
			Vector3 m_position = Vector3::Zero;						//���W�B
			Vector3 m_emissionColor = Vector3::Zero;				//���Ȕ����J���[�B
			bool m_isDirty = false;									//�_�[�e�B�t���O�B
			std::wstring m_skyCubeMapFilePath = L"Assets/modelData/preset/skyCubeMap.dds";		//��̃L���[�u�}�b�v�̃t�@�C���p�X�B
			std::string m_skyModelFilePath = "Assets/modelData/preset/Sky.tkm";					//���tkm�t�@�C���̃t�@�C���p�X�B
			ModelInitData m_modelData;
		};//class CSky;

	}//namespace prefab;
}//namespace Engine;

