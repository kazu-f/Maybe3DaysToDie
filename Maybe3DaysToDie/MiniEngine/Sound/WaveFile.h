#pragma once

/// <summary>
/// wave�t�@�C���B
/// </summary>

namespace Engine {
	/// <summary>
	/// wave�t�@�C�����������߂̃N���X�B
	/// </summary>
	/// <remarks>
	/// <para>wave�t�@�C���̓����ǂݍ��݁A�񓯊��ǂݍ��݂��T�|�[�g����B</para>
	/// <para>CWave::Read�͓����ǂݍ��݁ACWaveFile::ReadAsync�͔񓯊��ǂݍ��݂��s����B</para>
	/// </remarks>
	class CWaveFile : Noncopyable
	{
	public:
		CWaveFile();
		~CWaveFile();
		/// <summary>
		/// wave�t�@�C�����I�[�v���B
		/// </summary>
		/// <param name="fileName">�t�@�C�����B</param>
		/// <returns>false��Ԃ�����I�[�v���Ɏ��s�B</returns>
		bool Open(const wchar_t* fileName);
		/// <summary>
		/// �g�`�f�[�^��ǂݍ��ށB
		/// </summary>
		/// <param name="pBuffer">�g�`�f�[�^���������ރo�b�t�@�B</param>
		/// <param name="sizeToRead">�ǂݍ��ރf�[�^�T�C�Y</param>
		/// <param name="currentReadSize"></param>
		void Read(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);
		/// <summary>
		/// �g�`�f�[�^��񓯊��ǂݍ��݁B
		/// </summary>
		/// <param name="pBuffer">�g�`�f�[�^���������ރo�b�t�@�B</param>
		/// <param name="sizeToRead">�ǂݍ��ރf�[�^�T�C�Y�B</param>
		/// <param name="currentReadSize"></param>
		void ReadAsync(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);
		/// <summary>
		/// �ǂݍ��ݏI������B
		/// </summary>
		bool IsReadEnd()const
		{
			return m_isReadEnd;
		}
		/// <summary>
		/// �g�`�f�[�^�̃V�[�N�ʒu�����Z�b�g�B
		/// </summary>
		void ResetFile();
		/// <summary>
		/// �����[�X�B
		/// </summary>
		void Release();
		/// <summary>
		/// �t�@�C���T�C�Y���擾�B
		/// </summary>
		DWORD GetSize()const
		{
			return m_dwSize;
		}
		/// <summary>
		/// �t�@�C���t�H�[�}�b�g���擾�B
		/// </summary>
		WAVEFORMATEX* GetFormat()const
		{
			return m_pwfx;
		}
		/// <summary>
		/// �t�@�C���p�X�̃n�b�V���l���擾�B
		/// </summary>
		unsigned int GetFilePathHash()const
		{
			return m_filePathHash;
		}
		/// <summary>
		/// �ǂݍ��ݐ�̃o�b�t�@���m�ہB
		/// </summary>
		void AllocReadBuffer(int size)
		{
			m_readBuffer.reset(new char[size]);
		}
		/// <summary>
		/// �ǂݍ��ݐ�̃o�b�t�@���擾�B
		/// </summary>
		char* GetReadBuffer()
		{
			return m_readBuffer.get();
		}
	private:
		std::unique_ptr<char[]> m_readBuffer = nullptr;		//�ǂݍ��ݐ�̃o�b�t�@�B
		HMMIO	m_hmmio = nullptr;							//Wave�t�@�C���n���h���B
		WAVEFORMATEX* m_pwfx = nullptr;						//Wave�t�@�C���̃t�H�[�}�b�g��`�B
		MMCKINFO	m_ckRiff;								//
		DWORD		m_dwSize = 0;							//Wave�t�@�C���̃T�C�Y�B
		MMCKINFO	m_ck;									//�}���`���f�B�ARIFF�`�����N�B
		BYTE* m_pbData = nullptr;							//
		BYTE* m_pbDataCur = nullptr;						//
		ULONG m_ulDataSize = 0;								//�f�[�^�T�C�Y�H
		volatile bool	m_isReadEnd = true;					//�ǂݍ��ݏI���t���O�B
		std::thread		m_readAsyncThread;					//�񓯊��ǂݍ��݃X���b�h�B
		bool			m_isInvokeReadAsyncThread = false;	//
		std::wstring	m_filePath;							//�t�@�C���p�X�B
		unsigned int	m_filePathHash = 0;					//�t�@�C���p�X�̃n�b�V���R�[�h�B
	};

}

