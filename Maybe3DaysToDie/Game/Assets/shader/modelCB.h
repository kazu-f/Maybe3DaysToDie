

//���f���p�̒萔�o�b�t�@
cbuffer ModelCb : register(b0) {
	float4x4 mWorld			: packoffset(c0);
	float4x4 mView			: packoffset(c4);
	float4x4 mProj			: packoffset(c8);
	float3 emissionColor	: packoffset(c12);			//���Ȕ������B
	int isShadowReceiver	: packoffset(c12.w);		//�V���h�E���V�[�o�[�B
};

/*
*	���C�g�p�̒萔�o�b�t�@
*	tkLightManager.h��SLightParam�ƑΉ�����B
*/
cbuffer lightCb : register(b1)
{
	float3 eyePos			: packoffset(c0);		//�J�����̈ʒu�B
	int numDirectionLight	: packoffset(c0.w);		//�f�B���N�V�������C�g�̐��B
	float3 ambientLight		: packoffset(c1);		//�A���r�G���g���C�g�B
	int numPointLight		: packoffset(c1.w);		//�|�C���g���C�g�̐��B
	float4 screenParam		: packoffset(c2);		//�X�N���[���p�����[�^(neae,far,screenW,screenH)
}

/*
*	�}�e���A���̒萔�o�b�t�@
*	Material.h��SMaterialParam�ɑΉ�����B
*/
cbuffer MaterialParamCb : register(b2) {
	int hasNormalMap		: packoffset(c0.x);		//�@���}�b�v������H
	int hasSpecularMap		: packoffset(c0.y);		//�X�y�L�����}�b�v������H
	int hasReflectionMap	: packoffset(c0.z);		//���˃}�b�v������H
}
