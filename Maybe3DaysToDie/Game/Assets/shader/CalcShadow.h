
Texture2D<float4> shadowMap_0 : register(t6);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_1 : register(t7);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_2 : register(t8);		//�V���h�E�}�b�v�B

//�V���h�E�}�b�v�̐�
static const int NUM_SHADOW_MAP = 3;
/*
*	�V���h�E�}�b�v�p�̒萔�o�b�t�@�B
*	ShadowMap.h��SShadowCb�ɑΉ�����B
*/
cbuffer ShadowCb : register(b3) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��B
	float4 texOffset[NUM_SHADOW_MAP];	//�V���h�E�}�b�v�̃T�C�Y�B
	float4 depthOffset;	//�[�x�I�t�Z�b�g�B�V���h�E�A�N�l(�`����)����̂��߂̃o�C�A�X�B
										//�l���傫���قǉe�������ɂ����Ȃ�B
	float4 shadowAreaDepthInViewSpace;	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
																		//�Ȃ񂩔z�񂾂Ƒ���Ȃ���ł���...
}
/*
*	�e�������Ă��邩���v�Z����B
*/
float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float shadow_val = tex.Sample(g_sampler, uv).r;
	if (depth > shadow_val + dOffset) {
		return 1.0f;
	}
	return 0.0f;
}

/*
*	�J�X�P�[�h�C���f�b�N�X�̎擾�B
*/
int GetCascadeIndex(float zInView)
{
	[unroll]
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		if (zInView < shadowAreaDepthInViewSpace[i]) {
			return i;
		}
	}
	return -1;
}

/*
*	�J�X�P�[�h�V���h�E�̏����B
*/
float CalcShadow(float3 worldPos, float zInView, int shadowReceiverFrag)
{
	float shadow = 0.0f;
	if (shadowReceiverFrag) {
		//�e�𗎂Ƃ��B
		//�g�p����V���h�E�}�b�v�ԍ��̎擾�B
		int cascadeIndex = GetCascadeIndex(zInView);
		if (cascadeIndex == -1) {
			return shadow;
		}

		float4 posInLVP = mul(mLVP[cascadeIndex], float4(worldPos, 1.0f));
		posInLVP.xyz /= posInLVP.w;

		float depth = min(posInLVP.z, 1.0f);

		//uv���W�ϊ��B
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);

		if (cascadeIndex == 0) {
			shadow = CalcShadowPercent(shadowMap_0, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.x);
		}
		if (cascadeIndex == 1) {
			shadow = CalcShadowPercent(shadowMap_1, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.y);
		}
		if (cascadeIndex == 2) {
			shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[cascadeIndex], depth, depthOffset.z);
		}
	}
	return shadow;
}
