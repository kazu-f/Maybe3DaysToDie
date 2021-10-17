#pragma once

namespace Engine {
	/// <summary>
	/// Null�e�N�X�`���}�b�v��ێ�����N���X�B
	/// </summary>
	/// <remarks>
	/// �e�N�X�`�����ݒ肳��ĂȂ����Null�e�N�X�`����K�p������B
	/// Spec�}�b�v�Ȃ�0,Normal�}�b�v�Ȃ牚�ʖ����A���˃}�b�v�Ȃ�0�̃}�b�v�ƂȂ�B
	/// </remarks>
	class NullTextureMaps
	{
	public:
		/// <summary>
		/// Null�e�N�X�`���}�b�v��ǂݍ��݁B
		/// </summary>
		void Init();

	public:	//�A���x�h�B
		/// <summary> 
		/// �A���x�h�}�b�v���擾�B
		/// </summary>
		const std::unique_ptr<char[]>& GetAlbedoMap() const
		{
			return m_albedoMap;
		}
		/// <summary>
		/// �A���x�h�}�b�v�̃T�C�Y���擾�B
		/// </summary>
		unsigned int GetAlbedoMapSize() const
		{
			return m_albedoMapSize;
		}
		/// <summary>
		/// �A���x�h�}�b�v�̃t�@�C���p�X���擾�B
		/// </summary>
		const char* GetAlbedoMapFilePath() const
		{
			return m_albedoMapFileName.c_str();
		}

	public:	//�@���}�b�v�B
		/// <summary>
		/// �@���}�b�v���擾�B
		/// </summary>
		const std::unique_ptr<char[]>& GetNormalMap() const
		{
			return m_normalMap;
		}
		/// <summary>
		/// �@���}�b�v�̃T�C�Y���擾�B
		/// </summary>
		unsigned int GetNormalMapSize() const
		{
			return m_normalMapSize;
		}
		/// <summary>
		/// �@���}�b�v�̃t�@�C���p�X���擾�B
		/// </summary>
		const char* GetNormalMapFilePath() const
		{
			return m_normalMapFileName.c_str();
		}

	public:	//�X�y�L�����B
		/// <summary>
		/// �X�y�L�����}�b�v���擾�B
		/// </summary>
		const std::unique_ptr<char[]>& GetSpecularMap() const
		{
			return m_specularMap;
		}
		/// <summary>
		/// �X�y�L�����}�b�v�̃T�C�Y���擾�B
		/// </summary>
		unsigned int GetSpecularMapSize() const
		{
			return m_specularMapSize;
		}
		/// <summary>
		/// �X�y�L�����}�b�v�̃t�@�C���p�X���擾�B
		/// </summary>
		const char* GetSpecularMapFilePath() const
		{
			return m_specularMapFileName.c_str();
		}

	public:	//���t���N�V�����}�b�v�B(0�}�b�v)
		/// <summary>
		/// ���t���N�V�����}�b�v���擾�B
		/// </summary>
		const std::unique_ptr<char[]>& GetReflectionMap() const
		{
			return m_zeroValueMap;
		}
		/// <summary>
		/// ���t���N�V�����}�b�v�̃T�C�Y���擾�B
		/// </summary>
		/// <returns></returns>
		unsigned int GetReflectionMapSize() const
		{
			return m_zeroValueMapSize;
		}
		/// <summary>
		/// ���˃}�b�v�̃t�@�C���p�X���擾�B
		/// </summary>
		const char* GetReflectionMapFilePath() const
		{
			return m_zeroValueMapFileName.c_str();
		}

	public:	//���܃}�b�v�B(0�}�b�v)
		/// <summary>
		/// ���܃}�b�v���擾�B
		/// </summary>
		/// <returns></returns>
		const std::unique_ptr<char[]>& GetRefractionMap() const
		{
			return m_zeroValueMap;
		}
		/// <summary>
		/// ���܃}�b�v�̃T�C�Y���擾�B
		/// </summary>
		/// <returns></returns>
		unsigned int GetRefractionMapSize() const
		{
			return m_zeroValueMapSize;
		}
		/// <summary>
		/// ���܃}�b�v�̃t�@�C���p�X�擾�B
		/// </summary>
		const char* GetRefractionMapFilePath() const
		{
			return m_zeroValueMapFileName.c_str();
		}


	private:
		std::string m_albedoMapFileName;			//�A���x�h�}�b�v�̃t�@�C�����B
		std::string m_normalMapFileName;			//�@���}�b�v�̃t�@�C�����B
		std::string m_specularMapFileName;			//�X�y�L�����}�b�v�̃t�@�C�����B
		std::string m_zeroValueMapFileName;		//���t���N�V�����}�b�v�̃t�@�C�����B

		std::unique_ptr<char[]>	m_albedoMap;		//���[�h���ꂽ�A���x�h�}�b�v�B(dds�t�@�C��)
		unsigned int m_albedoMapSize;				//�A���x�h�}�b�v�̃T�C�Y�B(dds�t�@�C��)

		std::unique_ptr<char[]>	m_normalMap;		//���[�h���ꂽ�@���}�b�v�B(dds�t�@�C��)
		unsigned int m_normalMapSize;				//�@���}�b�v�̃T�C�Y�B

		std::unique_ptr<char[]>	m_specularMap;		//���[�h���ꂽ�X�y�L�����}�b�v�B(dds�t�@�C��)
		unsigned int m_specularMapSize;				//�X�y�L�����}�b�v�̃T�C�Y�B(dds�t�@�C��)

		std::unique_ptr<char[]> m_zeroValueMap;		//0�̒l���i�[���Ă���}�b�v�B
		unsigned int m_zeroValueMapSize = 0;		//0�̒l���i�[���Ă���}�b�v�̃T�C�Y�B
	};
}

