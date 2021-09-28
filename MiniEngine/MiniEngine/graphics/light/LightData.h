#pragma once

/// <summary>
/// �e�탉�C�g�̃f�[�^
/// </summary>

namespace Engine
{
	/// <summary>
	/// �f�B���N�V�������C�g�B
	/// </summary>
	struct SDirectionLight {
		Vector4 color;		//���C�g�̃J���[�B
		Vector3 direction;	//���C�g�̕����B
		unsigned int lightingMaterialIDGroup;
	};

	/// <summary>
	/// �A���r�G���g���C�g�B
	/// </summary>
	struct SAmbientLight {
		Vector3 color;			//�����̐F�B
	};
	/// <summary>
	/// �|�C���g���C�g�B
	/// </summary>
	struct SPointLight
	{
		Vector3		position;		//�|�C���g���C�g�̈ʒu�B
		Vector3		positionInView;	//�r���[��Ԃł̃|�C���g���C�g�̍��W�B
		Vector4		color;			//�|�C���g���C�g�̃J���[�B
		Vector4		attn;			//�����萔�Bx:�|�C���g���C�g�̉e�����͂��͈́By:�|�C���g���C�g�̌������B
									//y���傫���Ȃ�ƁA�����������Ȃ�B1.0�Ő��`�̌������ɂȂ�Bz,w:���g�p�B
		Vector4		directionAndAngle;	//�w�������C�g�̕����ƏƎˊp�x�B
										//xyz�ɕ����Aw�Ɋp�x(���W�A���P��)������B
										//hasDirection��1�̎��ɗL���ƂȂ�B
		unsigned int hasDirection;		//���̃|�C���g���C�g���w�������C�g���ǂ����̃t���O�B(�X�|�b�g���C�g���ǂ����B)
		unsigned int lightingMaterialIDGroup;	//���C�g�̉e����^����}�e���A��ID�̃O���[�v�B
	};
	///// <summary>
	///// �X�|�b�g���C�g�B
	///// </summary>
	//struct SSpotLight {
	//	Vector3		position;			//�X�|�b�g���C�g�̈ʒu�B
	//	Vector4		directionAndAngle;	//���C�g�̕����ƏƎˊp�x�B	
	//									//xyz�ɕ����Aw�Ɋp�x(���W�A���P��)������B
	//	Vector3		color;				//�X�|�b�g���C�g�̃J���[�B
	//	Vector4		attn;				//�����萔�Bx:�|�C���g���C�g�̉e�����͂��͈́By:�X�|�b�g���C�g�̌������B
	//									//y���傫���Ȃ�ƁA�����������Ȃ�B1.0�Ő��`�̌������ɂȂ�Bz,w:���g�p
	//	unsigned int lightingMaterialIDGroup;	//���C�g�̉e����^����}�e���A��ID�̃O���[�v�B
	//};
}