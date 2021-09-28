#pragma once

/// <summary>
/// �O���t�B�b�N�Ɋւ���ݒ�B
/// </summary>

namespace Engine {

	/// <summary>
	/// �V���h�E�}�b�v�̃R���t�B�O�B
	/// </summary>

	static const int NUM_SHADOW_MAP = 3;		//�V���h�E�}�b�v�̐��B

	struct SShadowMapConfig
	{
		bool 	isEnable = true;				//�e�𗎂Ƃ��������L�����ǂ����̃t���O�B
		int		shadowMapWidth = 4096;			//�V���h�E�}�b�v�̕��B
		int		shadowMapHeight = 4096;			//�V���h�E�}�b�v�̍����B
		float	lightHeight = 1000.0f;			//���C�g�̍����B
		float	depthOffset[NUM_SHADOW_MAP] = { 0.0002f , 0.0002f , 0.0002f };	//!<�V���h�E�I�t�Z�b�g�B���̒l��傫������ƁA�e�������ɂ����Ȃ�B
		float	shadowAreas[NUM_SHADOW_MAP] = { 2000.0f ,4000.0f , 20000.0f };			//�e��������͈́B
		//float	offsetTexelWorld = 0.05f;			//!<�u���[�̎��Ƀt�F�b�`����I�t�Z�b�g���W�B���[���h��Ԃ̗ʁB�l���傫���قǑ傫���{�P��B
	};

	struct STonemapConfig {
		bool isEnable = false;
		float luminance = 0.34f;		//���邳�B�l���傫���قǖ��邭�Ȃ�B
	};

	struct SPostEffectConfig
	{
		STonemapConfig tonemap;					//�g�[���}�b�v�̐ݒ�B
		bool isBloom = true;					//�u���[����L���ɂ��邩�H
		bool isFxaa = true;						//�A���`�G�C���A�X��L���ɂ��邩�H
	};

	struct SGraphicsConfig
	{
		SShadowMapConfig shadowConf;
		SPostEffectConfig postEffectConf;
	};

}