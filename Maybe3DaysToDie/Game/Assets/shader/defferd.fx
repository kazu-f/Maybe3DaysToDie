/*
	�f�B�t�@�[�h�V�F�[�f�B���O
*/

#include "modelCB.h"
#include "LightStruct.h"
#include "modelStruct.h"
#include "PBR.h"
#include "Fog.h"

//cbuffer PSDefferdCb : register(b0)
//{
//	float4x4 mViewProjInv;	//�r���[�v���W�F�N�V�����s��̋t�s��B
//};

cbuffer cb : register(b0) {
	float4x4 mvpInv;
};

struct VSDefferdInput {
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSDefferdInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> g_albedoMap : register(t0);	//�A���x�h
Texture2D<float4> g_normalMap : register(t1);	//�@���B
Texture2D<float4> g_worldPosMap : register(t2);	//���[���h���W�B
Texture2D<float4> g_specularMap : register(t3);	//�X�y�L�����B
Texture2D<float> g_shadowMap : register(t4);	//�V���h�E�B
Texture2D<float> g_reflectionMap : register(t5);	//���˗��B
TextureCube<float4> g_cubeMap : register(t6);	//�L���[�u�}�b�v�B

StructuredBuffer<SDirectionalLight> directionalLight : register(t7);	//���C�g�B

//�T���v���X�e�[�g�B
sampler g_sampler : register(s0);

//���C�g�̋P�x�B
static const float LIGHT_LUMINANCE = float3(0.298912, 0.586611, 0.114478);

//�f�B�t�@�[�h�p�̒��_�V�F�[�_�[�B
PSDefferdInput VSMain(VSDefferdInput In)
{
	PSDefferdInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain(PSDefferdInput psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	
	float3 normal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;	//�@���B
	normal = normal * 2.0f - 1.0f;
	float3 worldPos = g_worldPosMap.Sample(g_sampler, psIn.uv).xyz;	//���[���h���W�B
	float4 specMap = g_specularMap.Sample(g_sampler, psIn.uv);	//�X�y�L�����B
	float shadow = g_shadowMap.Sample(g_sampler, psIn.uv);		//�V���h�E�B
	float reflection = g_reflectionMap.Sample(g_sampler, psIn.uv);		//�V���h�E�B

	float3 lig = 0;		//���C�g
	float3 toEye = (eyePos - worldPos);		//�_���王�_�܂ł̐��K���x�N�g��
	float len = length(toEye);
	toEye = normalize(toEye);
	float spec = specMap.a;			//�X�y�L�����}�b�v��r�`�����l���ɃX�y�L�������x�B
	float roughness = 1.0f - spec;			//�g�U���˂̖ʂ̑e���B
	float metaric = specMap.r;		//g�`�����l���ɋ����x�B

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		//if (shadow < 0.9f) {
			//�����o�[�g�g�U���˂̐F�B
			float3 baseColor = saturate(dot(normal, -directionalLight[ligNo].direction)) * directionalLight[ligNo].color.xyz / PI;
			//DisneyModel�g�U����
			float disneyDiffuse = NormalizedDisneyDiffuse(normal, -directionalLight[ligNo].direction, toEye, roughness);
			float3 diffuse = baseColor * disneyDiffuse;

			//return float4(diffuse, 1.0f);
			
			//�N�b�N�g�����X���f���̋��ʔ���
			//float3 specCol = CookTrranceSpecular(-directionalLight[ligNo].direction, toEye, normal, metaric) * directionalLight[ligNo].color.xyz;
			float ligLum = dot(LIGHT_LUMINANCE, directionalLight[ligNo].color.xyz);
			float specPower = CookTrranceSpecular(-directionalLight[ligNo].direction, toEye, normal, spec);
			//���ʔ��ˌ��̌��͋����x���オ��ƁA�ގ��̐F�ɂȂ�B
			float3 specCol = lerp(directionalLight[ligNo].color.xyz, albedoColor * ligLum, metaric) * specPower;
			//return float4(specCol, 1.0f);
			//�g�U���ˌ��Ƌ��ʔ��ˌ�����`�⊮�B
			lig += lerp(diffuse, specCol, spec);

			//return float4(lig, 1.0f);

			//float specTerm = length(albedoColor.xyz * metaric);
			//specCol *= lerp(float3(specTerm, specTerm, specTerm), albedoColor.xyz, metaric);
			//lig += diffuse * (1.0f - specTerm) + specCol;
		//}
	}

	lig *= lerp(1.0f, 0.1f, shadow);
	//�����B
	lig += ambientLight;

	//�ŏI�I�ȐF�����肷��B
	
	float4 refColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	//�e�łȂ��Ȃ���}�b�v�B
	if (shadow < 0.9f) {
		refColor = g_cubeMap.Sample(g_sampler, reflect(toEye, normal));
	}
	reflection *= refColor.a;
	float4 finalColor = 1.0f;
	finalColor.xyz = albedoColor * (1.0f - reflection) + refColor.xyz * reflection;
	
	finalColor.xyz = finalColor.xyz * lig;

	//���̌v�Z�B
	finalColor = CalcFog(finalColor, len);

	finalColor.a = albedoColor.a;
	return finalColor;
}

