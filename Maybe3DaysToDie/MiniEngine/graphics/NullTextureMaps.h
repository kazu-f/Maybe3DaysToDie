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


	private:
		std::string m_albedoMapFileName;			//�A���x�h�}�b�v�̃t�@�C�����B
		std::string m_normalMapFileName;			//�@���}�b�v�̃t�@�C�����B
		std::string m_specularMapFileName;		//�X�y�L�����}�b�v�̃t�@�C�����B
		std::string m_reflectionMapFileName;		//���t���N�V�����}�b�v�̃t�@�C�����B
		std::string m_refractionMapFileName;		//���ܗ��}�b�v�̃t�@�C�����B

		std::unique_ptr<char[]>	m_albedoMap;		//���[�h���ꂽ�A���x�h�}�b�v�B(dds�t�@�C��)
		unsigned int m_albedoMapSize;				//�A���x�h�}�b�v�̃T�C�Y�B(dds�t�@�C��)

		std::unique_ptr<char[]>	m_normalMap;		//���[�h���ꂽ�@���}�b�v�B(dds�t�@�C��)
		unsigned int m_normalMapSize;				//�@���}�b�v�̃T�C�Y�B

		std::unique_ptr<char[]>	m_specularMap;	//���[�h���ꂽ�X�y�L�����}�b�v�B(dds�t�@�C��)
		unsigned int m_specularMapSize;			//�X�y�L�����}�b�v�̃T�C�Y�B(dds�t�@�C��)

		std::unique_ptr<char[]>	m_reflectionMap;	//���[�h���ꂽ���t���N�V�����}�b�v�B(dds�t�@�C��)
		unsigned int m_reflectionMapSize;			//���t���N�V�����}�b�v�̃T�C�Y�B

		std::unique_ptr<char[]>	m_refractionMap;	//���[�h���ꂽ���ܗ��}�b�v�B(dds�t�@�C��)
		unsigned int m_refractionMapSize;			//���ܗ��}�b�v�̃T�C�Y�B(dds�t�@�C��)
	};
}

