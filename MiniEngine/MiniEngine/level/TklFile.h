#pragma once
/// <summary>
/// tkl�t�@�C��
/// </summary>
/// <remarks>
/// tkl�t�@�C���̓��x���t�H�[�}�b�g�B
/// ���̃N���X��tkl�t�@�C����ǂݍ��ރN���X�B
/// </remarks>

namespace Engine {
	class CTklFile
	{
	public:
		/// <summary>
		/// �I�u�W�F�N�g�B
		/// </summary>
		struct SObject {
			std::unique_ptr<char[]> name;		//���f���̖��O�B
			int parentNo = -1;					//�e�̔ԍ��B
			float bindPose[4][3] = { 0.0f };	//�o�C���h�|�[�Y�B
			float invBindPose[4][3] = { 0.0f };	//�o�C���h�|�[�Y�̋t�s��B
			int no = 0;							//�I�u�W�F�N�g�̔ԍ��B
			bool isShadowCaster = false;		//�V���h�E�L���X�^�[�t���O�B
			bool isShadowReceiver = false;		//�V���h�E���V�[�o�[�t���O�B

			std::vector<int> intDatas;							//int�p�����[�^�B
			std::vector<float> floatDatas;						//float�p�����[�^�B
			std::vector<std::unique_ptr<char[]>> charsDatas;	//������B
			std::vector<Vector3> vec3Datas;						//vector3�̃p�����[�^�B
		};
		/// <summary>
		/// �ǂݍ��ݏ����B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		void Load(const char* filePath);
		/// <summary>
		/// �I�u�W�F�N�g�ɑ΂��ăN�G�����s���B
		/// </summary>
		/// <param name="query"></param>
		void QueryObject(std::function<void(SObject& obj)> query)
		{
			for (auto& obj : m_objects) {
				query(obj);
			}
		}
	private:
		int m_tklVersion = 100;		//tkl�t�@�C���̃o�[�W�����B
		int m_numObject = 0;		//�I�u�W�F�N�g�̐��B
		std::vector<SObject> m_objects;		//�I�u�W�F�N�g�̃��X�g�B
		bool m_isLoaded = false;	//�ǂݍ��ݍς݂��H
	};
}

