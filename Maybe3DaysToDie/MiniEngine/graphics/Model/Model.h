#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "../Skeleton.h"
namespace Engine {
	enum ModelUpAxis {
		enModelUpAxis_Z,	//Z�A�b�v
		enModelUpAxis_Y,	//Y�A�b�v�B
	};
	class IShaderResource;

	/// <summary>
	/// ���f���̏������f�[�^
	/// </summary>
	struct ModelInitData {
		const char* m_tkmFilePath = nullptr;		//tkm�t�@�C���p�X�B
		SShaderInitData m_shaderData;				//�ǂݍ��ރV�F�[�_�[�̃f�[�^�B���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�̗������w�肷��K�v������B
		void* m_expandConstantBuffer = nullptr;		//���[�U�[�g���̒萔�o�b�t�@�B
		int m_expandConstantBufferSize = 0;			//���[�U�[�g���̒萔�o�b�t�@�̃T�C�Y�B
		IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B1111
		Skeleton* m_skeleton = nullptr;					//�X�P���g���f�[�^�B
		StructuredBuffer* m_instancingDataSB = nullptr;			//�C���X�^���V���O�`��p��SB�B
		ModelUpAxis m_modelUpAxis = enModelUpAxis_Z;	//���f���̏�����B
	};
	/// <summary>
	/// ���f���N���X�B
	/// </summary>
	class Model {
	public:
		/// <summary>
		/// tkm�t�@�C�����珉�����B
		/// </summary>
		/// <param name="initData">�������f�[�^</param>
		void Init(const ModelInitData& initData,int maxInstance = 1);
		/// <summary>
		/// ���[���h�s��̍X�V�B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
		{
			m_world = CalcWorldMatrix(pos, rot, scale);
		}


		/// <summary>
		/// ���[���h�s����v�Z
		/// </summary>
		/// <remark>
		/// Model�N���X�̐ݒ�Ɋ�Â������[���h�s��̌v�Z���s���܂��B
		/// �v�Z���ꂽ���[���h�s�񂪖߂�l�Ƃ��ĕԂ���܂��B
		/// �{�֐���UpdateWorldMatrix����Ă΂�Ă��܂��B
		/// �{�֐��̓��[���h�s����v�Z���āA�߂������ł��B
		/// Model::m_worldMatrix���X�V�����킯�ł͂Ȃ��̂ŁA���ӂ��Ă��������B
		/// �{�N���X�̐ݒ�Ɋ�Â��Čv�Z���ꂽ���[���h�s�񂪕K�v�ȏꍇ�Ɏg�p���Ă�������
		/// </remark>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		/// <returns>���[���h�s��</returns>
		Matrix CalcWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);

		/// <summary>
		/// �X�P���g�����֘A�t����B
		/// </summary>
		/// <param name="skeleton">�X�P���g��</param>
		void BindSkeleton(Skeleton& skeleton)
		{
			m_meshParts.BindSkeleton(skeleton);
		}

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
		void Draw(RenderContext& renderContext,int numInstance = 1);
		/// <summary>
		/// /�V���h�E�}�b�v�p�`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="mLVP">���C�g�r���[�v���W�F�N�V�����s��</param>
		void Draw(RenderContext& rc, Matrix mLVP, int numInstance = 1);
		/// <summary>
		/// �ʂ̃J��������`�悷��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="mView">�r���[�s��</param>
		/// <param name="mProj">�v���W�F�N�V�����s��</param>
		void Draw(RenderContext& rc,Matrix mView , Matrix mProj, int numInstance = 1);
		/// <summary>
		/// �������ς݂��H
		/// </summary>
		bool IsInited()
		{
			return m_tkmFile->IsLoaded();
		}
		/// <summary>
		/// ���[���h�s����擾�B
		/// </summary>
		/// <returns></returns>
		const Matrix& GetWorldMatrix() const
		{
			return m_world;
		}
		/// <summary>
		/// ���Ȕ����F��ݒ肷��B
		/// </summary>
		/// <param name="emission">���Ȕ����F�B</param>
		void SetEmissionColor(const Vector3& emission)
		{
			m_meshParts.SetEmissionColor(emission);
		}
		/// <summary>
		/// �V���h�E���V�[�o�[�ɐݒ肷��B
		/// </summary>
		void SetShadowReceiverFlag(bool flag)
		{
			m_meshParts.SetShadowReceiverFlag(flag);
		}
		/// <summary>
		/// tkm�t�@�C�����擾�B
		/// </summary>
		const TkmFile& GetTkmFile()const
		{
			return *m_tkmFile;
		}
		/// <summary>
		/// ���f���}�e���A���̌����B
		/// </summary>
		/// <param name="findMaterial">�}�e���A�����������Ƃ��ɌĂяo�����R�[���o�b�N�֐��B</param>
		void FindMaterial(OnFindMateral findMaterial)
		{
			m_meshParts.FindMaterial(findMaterial);
		}
	private:

		Matrix m_world;			//���[���h�s��B
		TkmFile* m_tkmFile;		//tkm�t�@�C���B
		MeshParts m_meshParts;	//���b�V���p�[�c�B
		ModelUpAxis m_modelUpAxis = enModelUpAxis_Z;	//���f���̏�����B
	};
}