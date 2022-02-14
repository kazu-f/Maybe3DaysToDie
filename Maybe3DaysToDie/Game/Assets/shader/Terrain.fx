#include "ShaderSampler.h"
#include "LightStruct.h"
#include "PBR.h"
#include "GBufferStruct.h"
#include "CalcShadow.h"

//�n�`�p�̒萔�o�b�t�@
cbuffer TerrainCb : register(b0) {
	float4x4 mWorld			: packoffset(c0);
	float4x4 mView			: packoffset(c4);
	float4x4 mProj			: packoffset(c8);
	int isShadowReceiver	: packoffset(c12.x);		//�V���h�E���V�[�o�[�B
};

//�n�`�p�̒萔�o�b�t�@
cbuffer TerrainShadowCb : register(b0) {
	float4x4 mWorldShadow			: packoffset(c0);
	float4x4 mTerrainLVP			: packoffset(c4);
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

//Terrain���_�V�F�[�_�[�ւ̓��́B
struct SVSInTerrain {
	float4 pos : POSITION;		//�n�`�̒��_���W�B
	float3 normal : NORMAL;		//�n�`�̖@���B
	float2 uv : TEXCOORD0;		//UV���W�B
	float texType[8] : TEXTYPE;		//�e�N�X�`����؂�ւ��邽�߂̕ϐ��B
};

struct SPSInTerrain {
	float4 pos : SV_POSITION;	//�X�N���[����Ԃł̃s�N�Z���̍��W�B
	float3 normal : NORMAL;		//�@���B
	float2 uv : TEXCOORD0;		//UV���W�B
	float3 worldPos : TEXCOORD1;	//���[���h��Ԃł̃s�N�Z���̍��W�B
	float texType[8] : TEXCOORD2;		//�e�N�X�`����؂�ւ��邽�߂̕ϐ��B
};

Texture2D<float4> g_albedoMap : register(t0);	//�A���x�h
StructuredBuffer<SDirectionalLight> directionalLight : register(t1);	//���C�g�B

Texture2D<float4> g_terrainMap[4] : register(t10);	//�n�`�p�̃e�N�X�`��

//Texture2D<float4> g_terrainMap1 : register(t10);	//�n�`�p�̃e�N�X�`��
//Texture2D<float4> g_terrainMap2 : register(t11);	//�n�`�p�̃e�N�X�`��
//Texture2D<float4> g_terrainMap3 : register(t12);	//�n�`�p�̃e�N�X�`��
//Texture2D<float4> g_terrainMap4 : register(t13);	//�n�`�p�̃e�N�X�`��

//�T���v���X�e�[�g�B
//sampler g_sampler : register(s0);

float4 CalcTerrainTexture(float2 uv,float type[8])
{
	float4 finalCol = 0.0f;
	//finalCol += g_terrainMap1.Sample(g_sampler, uv) * type[0].x;		//�A���x�h�B
	//finalCol += g_terrainMap2.Sample(g_sampler, uv) * type[0].y;		//�A���x�h�B
	//finalCol += g_terrainMap3.Sample(g_sampler, uv) * type[0].z;		//�A���x�h�B
	//finalCol += g_terrainMap4.Sample(g_sampler, uv) * type[0].w;		//�A���x�h�B

	for (int i = 0; i < 4; i++)
	{
		finalCol += g_terrainMap[i].Sample(g_sampler, uv) * type[i];		//�A���x�h�B

	}

	//finalCol += g_terrainMap[0].Sample(g_sampler, uv) * type[0];		//�A���x�h�B
	//finalCol += g_terrainMap[1].Sample(g_sampler, uv) * type[1];		//�A���x�h�B
	//finalCol += g_terrainMap[2].Sample(g_sampler, uv) * type[2];		//�A���x�h�B
	//finalCol += g_terrainMap[3].Sample(g_sampler, uv) * type[3];		//�A���x�h�B

	return finalCol;
}

/// <summary>
/// �n�`�p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g�B
/// </summary>
SPSInTerrain VSTerrainMain(SVSInTerrain vsIn)
{
	SPSInTerrain psIn;

	psIn.pos = mul(mWorld, vsIn.pos);						//���_�����[���h���W�n�ɕϊ��B
	psIn.worldPos = psIn.pos;								//���[���h���W������B
	psIn.pos = mul(mView, psIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	psIn.normal = vsIn.normal;
	psIn.uv = vsIn.uv;
	//psIn.texType[0] = vsIn.texType[0];
	//psIn.texType[1] = vsIn.texType[1];
	for (int i = 0; i < 8; i++)
	{
		psIn.texType[i] = vsIn.texType[i];
	}

	return psIn;
}

//���C�g�̋P�x�B
static const float LIGHT_LUMINANCE = float3(0.298912, 0.586611, 0.114478);
float4 PSTerrainMain(SPSInTerrain psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	float3 normal = psIn.normal;
	float3 toEye = normalize(eyePos - psIn.worldPos);		//�_���王�_�܂ł̐��K���x�N�g��
	float metaric = 0.0f;			//�����x�B
	float spec = 0.0f;
	float roughness = 1.0f - spec;			//�g�U���˂̖ʂ̑e���B

	float3 lig = float3(0.0f,0.0f,0.0f);		//���C�g
	
	//�V���h�E�B
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	float shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);
	//float shadow = 0.0f;

	for (int ligNo = 0; ligNo < numDirectionLight; ligNo++)
	{
		if (shadow < 0.9f) {
			//�f�B�t�@�[�h�g�U���˂̐F�B
			float3 baseColor = saturate(dot(normal, -directionalLight[ligNo].direction)) * directionalLight[ligNo].color.xyz / PI;
			//DisneyModel�g�U����
			float disneyDiffuse = NormalizedDisneyDiffuse(normal, -directionalLight[ligNo].direction, toEye, roughness);
			float3 diffuse = baseColor * disneyDiffuse;

			//�N�b�N�g�����X���f���̋��ʔ���
			float ligLum = dot(LIGHT_LUMINANCE, directionalLight[ligNo].color.xyz);
			float specPower = CookTrranceSpecular(-directionalLight[ligNo].direction, toEye, normal, spec);
			//���ʔ��ˌ��̌��͋����x���オ��ƁA�ގ��̐F�ɂȂ�B
			float3 specCol = lerp(directionalLight[ligNo].color.xyz, albedoColor * ligLum, metaric) * specPower;

			//�g�U���ˌ��Ƌ��ʔ��ˌ�����`�⊮�B
			lig += lerp(diffuse, specCol, spec);
		}
	}

	//�����B
	lig += ambientLight;

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.xyz = float3(0.0f,1.0f,0.0f) * lig;
	finalColor.a = 1.0f;

	return finalColor;
}

//GBuffer�ɏ������ރs�N�Z���V�F�[�_�[�̃G���g���֐��B
PSOut_GBuffer PSMain_TerrainRenderGBuffer(SPSInTerrain psIn) {
	PSOut_GBuffer Out = (PSOut_GBuffer)0;

	Out.albedo = CalcTerrainTexture(psIn.uv, psIn.texType);		//�A���x�h�B
	//�@���}�b�v�B
	Out.normal.xyz = (psIn.normal / 2.0f) + 0.5f;

	//���[���h���W�B
	Out.worldPos = float4(psIn.worldPos, 0.0f);

	//�X�y�L�����}�b�v�B
	Out.specMap = 0.0f;

	//�V���h�E�B
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

	//���˗��B
	Out.reflection = 0.0f;

	return Out;
}

//�V���h�E�}�b�v�`��p�̒��_�V�F�[�_�[�̈����\���́B
struct SVSTerrainShadowIn {
	float4 pos : POSITION;
};
//�V���h�E�}�b�v�`��p�̃s�N�Z���V�F�[�_�[�̈����\���́B
struct SPSTerrainShadowIn {
	float4 pos : SV_POSITION;
};
/*
*	�V���h�E�}�b�v�������ݗp�̒��_�V�F�[�_�[�B
*/
SPSTerrainShadowIn VSTerrainMainShadowMap(SVSTerrainShadowIn vsIn)
{
	SPSTerrainShadowIn psIn;

	psIn.pos = mul(mWorldShadow, vsIn.pos);
	psIn.pos = mul(mTerrainLVP, psIn.pos);

	return psIn;
}

/*
*	�V���h�E�}�b�v�������ݗp�̃s�N�Z���V�F�[�_�[�B
*/
float4 PSTerrainMainShadowMap(SPSTerrainShadowIn psIn) :SV_Target0
{
	return psIn.pos.z / psIn.pos.w;
}