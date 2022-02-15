#pragma once

namespace Engine {

	class CResourceEngine : Noncopyable
	{
	public:
		/// <summary>
		/// tkm�t�@�C�����o���N����擾�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <returns>tkm�t�@�C���Bnullptr���Ԃ��Ă�����o���N�ɓo�^����Ă��Ȃ��B</returns>
		TkmFile* GetTkmFileFromBank(const char* filePath)
		{
			return m_tkmBank.Get(filePath);
		}
		/// <summary>
		/// tks�t�@�C�����o���N����擾�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <returns>tks�t�@�C���Bnullptr���Ԃ��Ă�����o���N�ɓo�^����Ă��Ȃ��B</returns>
		TksFile* GetTksFileFromBank(const char* filePath)
		{
			return m_tksBank.Get(filePath);
		}
		/// <summary>
		/// tkm�t�@�C�����o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath">tkm�t�@�C���p�X</param>
		/// <param name="tkmFile"></param>
		void RegistTkmFileToBank(const char* filePath, TkmFile* tkmFile)
		{
			m_tkmBank.Regist(filePath, tkmFile);
		}
		/// <summary>
		/// tks�t�@�C�����o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath">tks�t�@�C���p�X</param>
		/// <param name="tkmFile"></param>
		void RegistTksFileToBank(const char* filePath, TksFile* tksFile)
		{
			m_tksBank.Regist(filePath, tksFile);
		}
		/// <summary>
		/// �e�N�X�`�����o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <param name="texture">�e�N�X�`���B</param>
		void RegistTextureToBank(const char* filePath, Texture* texture)
		{
			m_textureBank.Regist(filePath, texture);
		}
		/// <summary>
		/// �o���N����e�N�X�`�����擾�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <returns>�e�N�X�`���B</returns>
		Texture* GetTextureFromBank(const char* filePath)
		{
			return m_textureBank.Get(filePath);
		}
		/// <summary>
		/// �V�F�[�_�[�t�@�C���o���N����V�F�[�_�[���擾�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		Shader* GetShaderFromBank(const char* filePath, const char* entryPointFuncName)
		{
			std::string programName = filePath;
			programName += entryPointFuncName;
			return m_shaderBank.Get(programName.c_str());
		}
		/// <summary>
		/// �V�F�[�_�[�t�@�C�����o���N�ɓo�^�B
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="shader"></param>
		void RegistShaderToBank(const char* filePath, const char* entryPointFuncName, Shader* shader)
		{
			std::string programName = filePath;
			programName += entryPointFuncName;
			m_shaderBank.Regist(programName.c_str(), shader);
		}
	private:
		TResourceBank<TkmFile> m_tkmBank;				//tkm�t�@�C���o���N�B
		TResourceBank<TksFile> m_tksBank;				//tks�t�@�C���o���N�B
		TResourceBank<Shader> m_shaderBank;				// �V�F�[�_�[�o���N
		TResourceBank<Texture>	m_textureBank;			// �e�N�X�`���o���N�B
	};

}

