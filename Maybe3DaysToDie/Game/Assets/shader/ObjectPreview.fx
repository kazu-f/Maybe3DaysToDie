#include "modelStruct.h"
#include "modelCB.h"

//���f���e�N�X�`���B
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);
//�T���v���X�e�[�g�B
sampler g_sampler : register(s0);

Texture2D<float4> shadowMap_0 : register(t6);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_1 : register(t7);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_2 : register(t8);		//�V���h�E�}�b�v�B

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
float CalcShadow(float3 worldPos, float zInView)
{
	float shadow = 0.0f;
	if (isShadowReceiver) {
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

//�@�����v�Z�B
float3 CalcNormal(float3 normal, float3 biNormal, float3 tangent, float2 uv)
{
	//�@���̌v�Z�B
	float3 ret;
	if (hasNormalMap) {
		//�@���}�b�v����@�������������Ă���B
		float3 binSpaceNormal = g_normalMap.Sample(g_sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;	//-1.0f�`1.0f�ɒ����B
		binSpaceNormal = normalize(binSpaceNormal);
		ret = tangent * binSpaceNormal.x		//�ڐ�(�@���ɑ΂��ĉE�H)
			+ biNormal * binSpaceNormal.y			//�]�@��(�@���ɑ΂��ď�)
			+ normal * binSpaceNormal.z;			//�@������
	}
	else {
		ret = normal;
	}
	return ret;
}

//GBuffer�ɏ������ރs�N�Z���V�F�[�_�[�̃G���g���֐��B
PSOut_GBuffer PSMain(SPSIn psIn) {
	PSOut_GBuffer Out = (PSOut_GBuffer)0;

	Out.albedo = g_texture.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	//Out.albedo = g_texture.SampleLevel(g_sampler, psIn.uv, 0);		//�A���x�h�B
	//�@���}�b�v�B
	float3 normal = CalcNormal(psIn.normal, psIn.biNormal, psIn.Tangent, psIn.uv);
	Out.normal.xyz = (normal / 2.0f) + 0.5f;

	//���[���h���W�B
	Out.worldPos = float4(psIn.worldPos, 0.0f);

	//�X�y�L�����}�b�v�B
	Out.specMap = 0.0f;
	if (hasSpecularMap) {
		//�X�y�L�����}�b�v������B
		Out.specMap = g_specularMap.Sample(g_sampler, psIn.uv);
	}

	//�V���h�E�B
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z);

	//���˗��B
	Out.reflection = g_reflectionMap.Sample(g_sampler, psIn.uv).xy;

	return Out;
}