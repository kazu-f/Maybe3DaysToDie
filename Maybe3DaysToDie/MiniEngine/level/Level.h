#pragma once

#include "TklFile.h"

namespace Engine {
	class CMapChip;
	class CMapChipRender;
	/// <summary>
	/// �I�u�W�F�N�g�f�[�^�B
	/// </summary>
	struct SLevelObjectData {
		Vector3 position;		//���W�B
		Quaternion rotation;	//��]�B
		Vector3 scale;			//�g�嗦�B
		const wchar_t* name;	//���O�B
		bool isShadowCaster;	//�V���h�E�L���X�^�[
		bool isShadowReceiver;	//�V���h�E���V�[�o�[
		/// <summary>
		/// �����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
		/// </summary>
		/// <param name="objName">���ׂ閼�O�B</param>
		/// <returns>���S��v��true��Ԃ��B</returns>
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}
		/// <summary>
		/// ���O���O����v���邩�𒲂ׂ�B
		/// </summary>
		/// <param name="n">���ׂ閼�O�B</param>
		/// <returns>�O����v����Ȃ�true��Ԃ��B</returns>
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//���O�������B�s��v�B
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};
	/// <summary>
	/// ���x���B
	/// </summary>
	class CLevel : Noncopyable
	{
	private:
		using CMapChipPtr = std::unique_ptr<CMapChip>;
		using CMapChipRenderPtr = std::unique_ptr<CMapChipRender>;
	public:
		CLevel();
		~CLevel();
		/// <summary>
		/// ���x��������������B
		/// </summary>
		/// <param name="filePath">tkl�t�@�C���̃t�@�C���p�X�B</param>
		/// <param name="hookFunc">�I�u�W�F�N�g���쐬����Ƃ��̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g</param>
		/// <remarks>
		/// �t�b�N���Ȃ��Ȃ�nullptr�w�肷��Ƃ����B
		/// �֐��I�u�W�F�N�g��false��Ԃ��ƁA�I�u�W�F�N�g�̏�񂩂�
		/// MapChip�N���X�̃C���X�^���X�����������B
		/// �I�u�W�F�N�g�̖��O�ȂǂŁA����ȃN���X�̃C���X�^���X�𐶐�����ꍇ��
		/// MapChip�N���X�̃C���X�^���X���s�v�Ȃ�true��Ԃ��ƍ���Ȃ��Ȃ�B
		/// </remarks>
		void Init(const char* filePath, std::function<bool(SLevelObjectData& objData)> hookFunc);
	private:
		/// <summary>
		/// �}�b�v�`�b�v�����_�[���쐬or�`�悷��I�u�W�F�N�g�̐����C���N�������g����B
		/// </summary>
		/// <remarks>
		/// ���o�^�̃I�u�W�F�N�g���n���ꂽ�Ƃ��́A�V���ɍ쐬�B
		/// �o�^�ς݂̏ꍇ�͕`�悷�ׂ��I�u�W�F�N�g�����C���N�������g�����B
		/// </remarks>
		void CreateMapChipRenderOrAddRenderObject(const SLevelObjectData& objData);
		/// <summary>
		/// �{�[���s��̍\�z�B
		/// </summary>
		void BuildBoneMatrices();
	private:
		std::vector<CMapChipPtr> m_mapChipPtrs;			//�}�b�v�`�b�v�̉ϒ��z��B
		std::map<unsigned int, CMapChipRender*> m_mapChipRenderPtrs;	//�}�b�v�`�b�v�����_�[�̉ϒ��z��B

		CTklFile m_tklFile;					//tkl�t�@�C���B
		static const int bone_MAX = 512;	//�I�u�W�F�N�g�̍ő吔�B
		using BonePtr = std::unique_ptr<Bone>;
		std::vector<BonePtr> m_bones;		//�{�[���̔z��B
		std::unique_ptr<Matrix[]> m_boneMatrixs;	//�{�[���s��B
		bool m_isInited = false;			//�������ς݂��ǂ����B
	};	//class CLevel;
}	//namespace Engine

