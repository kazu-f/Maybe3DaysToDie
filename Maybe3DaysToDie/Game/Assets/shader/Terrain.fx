#include "LightStruct.h"
#include "PBR.h"

//�n�`�p�̒萔�o�b�t�@
cbuffer TerrainCb : register(b0) {
	float4x4 mView			: packoffset(c0);
	float4x4 mProj			: packoffset(c4);
};

/*
*	���C�g�p�̒萔�o�b�t�@
*	tkLightManager.h��SLightParam�ƑΉ�����B
*/
cbuffer lightCb : register(b1)
{
	float3 eyePos			: packoffset(c0);		//�J�����̈ʒu�B
	int numDirectionLight : packoffset(c0.w);		//�f�B���N�V�������C�g�̐��B
	float3 ambientLight		: packoffset(c1);		//�A���r�G���g���C�g�B
	int numPointLight : packoffset(c1.w);		//�|�C���g���C�g�̐��B
	float4 screenParam		: packoffset(c2);		//�X�N���[���p�����[�^(neae,far,screenW,screenH)
}

//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn {
	float4 pos : POSITION;		//�n�`�̒��_���W�B
	float3 normal : NORMAL;		//�n�`�̖@���B
	float2 uv : TEXCOORD0;		//UV���W�B
};

struct SPSIn {
	float4 pos : SV_POSITION;	//�X�N���[����Ԃł̃s�N�Z���̍��W�B
	float3 normal : NORMAL;		//�@���B
	float2 uv : TEXCOORD0;		//UV���W�B
};

Texture2D<float4> g_albedoMap : register(t0);	//�A���x�h
StructuredBuffer<SDirectionalLight> directionalLight : register(t1);	//���C�g�B

//�T���v���X�e�[�g�B
sampler g_sampler : register(s0);

/// <summary>
/// �n�`�p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g�B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psIn;

	psIn.pos = mul(mView, vsIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	psIn.normal = vsIn.normal;
	psIn.uv = vsIn.uv;

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	float3 normal = psIn.normal;

	float3 lig = float3(0.0f,0.0f,0.0f);		//���C�g

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		//�f�B�t�@�[�h�g�U���˂̐F�B
		float3 baseColor = saturate(dot(normal, -directionalLight[ligNo].direction)) * directionalLight[ligNo].color.xyz / PI;

		//�g�U���ˌ��Ƌ��ʔ��ˌ�����`�⊮�B
		lig += baseColor;
	}

	//�����B
	lig += ambientLight;

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.xyz = float3(0.0f,1.0f,0.0f) * lig;
	finalColor.a = 1.0f;

	return finalColor;
}

