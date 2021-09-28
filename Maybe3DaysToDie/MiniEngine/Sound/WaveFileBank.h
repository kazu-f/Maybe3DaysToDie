#pragma once
/// <summary>
/// �g�`�f�[�^�o���N�B
/// </summary>

namespace Engine {
	class CWaveFile;
	typedef std::shared_ptr<CWaveFile> CWaveFilePtr;		//�g�`�f�[�^�̃V�F�A�[�h�|�C���^�B
	typedef std::map<unsigned int, CWaveFilePtr> CWaveFilePtrMap;	//�g�`�f�[�^�|�C���^�̃}�b�v�B

	/// <summary>
	/// �g�`�f�[�^�o���N�B
	/// </summary>
	/// <remarks>
	/// <para>��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^���邱�Ƃ��ł���B</para>
	/// <para>�o�^���ꂽ�g�`�f�[�^�͍ēǂݍ��݂��s���K�v�Ȃ��ɁA�o���N����ė��p���邱�Ƃ��ł���B</para>
	/// </remarks>
	class CWaveFileBank:Noncopyable
	{
	public:
		CWaveFileBank();
		~CWaveFileBank();
		/// <summary>
		/// �g�`�f�[�^��o�^�B
		/// </summary>
		/// <param name="groupID">�O���[�vID�B�ő�l��MAX_GROUP - 1�B</param>
		/// <param name="waveFile">�t�@�C���p�X�B</param>
		void RegistWaveFile(int groupID, CWaveFilePtr waveFile);
		/// <summary>
		/// �����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩�����B
		/// </summary>
		/// <param name="groupID">�O���[�vID�B�ő�l��MAX_GROUP - 1�B</param>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <returns>�g�`�f�[�^�B�o�^����Ă��Ȃ��ꍇ��NULL�B</returns>
		CWaveFilePtr FindWaveFile(int groupID, const wchar_t* filePath);
		/// <summary>
		/// �����Ŏw�肵���t�@�C���p�X�̖��O�L�[���o���N�ɓo�^����Ă��邩�����B
		/// </summary>
		/// <remarks>������̂ق������������Ȃ�B</remarks>
		/// <param name="groupID">�O���[�vID�B�ő�l��MAX_GROUP - 1�B</param>
		/// <param name="filePath"></param>
		/// <returns></returns>
		CWaveFilePtr FindWaveFile(int groupID, const WNameKey& nameKey);
		/// <summary>
		/// �g�`�f�[�^���o���N����o�^�����B
		/// </summary>
		/// <param name="groupID">�O���[�vID�B�ő�l��MAX_GROUP - 1�B</param>
		/// <param name="waveFile">�g�`�f�[�^�B</param>
		void UnregistWaveFile(int groupID, CWaveFilePtr waveFile);
		/// <summary>
		/// �O���[�v�P�ʂŉ���B
		/// </summary>
		/// <param name="groupID">�O���[�vID�B�ő�l��MAX_GROUP - 1�B</param>
		void Release(int groupID);
		/// <summary>
		/// �S�ẴO���[�v������B
		/// </summary>
		void ReleaseAll()
		{
			for (int i = 0; i < MAX_GROUP; i++) {
				Release(i);
			}
		}
	private:
		static const int MAX_GROUP = 256;
		CWaveFilePtrMap m_waveFileMap[MAX_GROUP];		//wave�t�@�C���̃��X�g�B
	};//class CWaveFileBank;

}//namespace Engine;

