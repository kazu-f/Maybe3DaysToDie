#pragma once

namespace Engine {
	//GBuffer�̒�`�B
	enum class EnGBuffer {
		enGBufferAlbed,			//�A���x�h�B
		enGBufferNormal,		//�@���B
		enGBufferWorldPos,		//���[���h���W�B
		enGBufferSpecular,		//�X�y�L�����B
		enGBufferShadow,		//�e�}�b�v�B
		enGBufferReflection,	//���˗��B
		enGBufferNum,			//GBuffer�̐��B
	};

	class CGBufferRender : Noncopyable
	{
	public:
		CGBufferRender();
		~CGBufferRender();
		/// <summary>
		/// �������B
		/// </summary>
		void Init();
		/// <summary>
		/// GBuffer���������ݐ�ɐݒ�B
		/// </summary>
		void BeginRender(RenderContext& rc);
		/// <summary>
		/// �������ݐ�����ɖ߂��B
		/// </summary>
		void EndRender(RenderContext& rc);
		/// <summary>
		/// �f�B�t�@�[�h�����_�����O�B
		/// </summary>
		void Render(RenderContext& rc);
	public:
		/// <summary>
		/// �f�B�t�@�[�h�����_�����O�֓o�^����B
		/// </summary>
		void RegistDefferdModel(prefab::ModelRender* caster) {
			m_defferdModelArray.push_back(caster);
		}
		/// <summary>
		/// �f�B�t�@�[�h�����_�����O�o�^����������B
		/// </summary>
		void RemoveDefferdModel(prefab::ModelRender* caster)
		{
			auto it = std::find(m_defferdModelArray.begin(), m_defferdModelArray.end(), caster);
			if (it != m_defferdModelArray.end()) {
				m_defferdModelArray.erase(it);
			}
		}
		/// <summary>
		/// �f�B�t�@�[�h���f���o�^���N���A�B
		/// </summary>
		/// <remarks>�G���W�����ŌĂяo���B</remarks>
		void ClearDefferdModel()
		{
			m_defferdModelArray.clear();
		}
	public:		/////Get�֐���
		/// <summary>
		/// �����_�����O�^�[�Q�b�g���擾�B
		/// </summary>
		/// <param name="enGBuffer"></param>
		/// <returns></returns>
		RenderTarget& GetRenderTarget(EnGBuffer enGBuffer)
		{
			return m_GBuffer[static_cast<int>(enGBuffer)];
		}
		/// <summary>
		/// GBuffer�̃e�N�X�`�����擾�B
		/// </summary>
		/// <param name="enGBuffer"></param>
		/// <returns></returns>
		Texture& GetGBufferTexture(EnGBuffer enGBuffer)
		{
			return m_GBuffer[static_cast<int>(enGBuffer)].GetRenderTargetTexture();
		}
	private:
		RenderTarget m_GBuffer[static_cast<int>(EnGBuffer::enGBufferNum)];		//GBuffer�B
		std::vector<prefab::ModelRender*> m_defferdModelArray;								//�f�B�t�@�[�h�ŕ`�悷�郂�f���B
	};	//////class CGBufferRender
}

