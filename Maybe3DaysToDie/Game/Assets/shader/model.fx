/*
*		���f���V�F�[�_�[�B
*/

#include "ShaderSampler.h"
#include "modelCB.h"
#include "LightStruct.h"
#include "modelStruct.h"
#include "PBR.h"
#include "Fog.h"
#include "CalcShadow.h"

//���f���e�N�X�`���B
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);
//�{�[���s��B
StructuredBuffer<float4x4> boneMatrix : register(t4);
//�f�B���N�V�������C�g�B
StructuredBuffer<SDirectionalLight> directionalLight : register(t5);

StructuredBuffer<float4x4> instancingDatas : register(t9);		//�C���X�^���V���O�`��p�̃f�[�^�B
//�T���v���X�e�[�g�B
//sampler g_sampler : register(s0);

//�X�L���s����v�Z����֐��B
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
		w += skinVert.Weights[i];
	}

	skinning += boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	return skinning;
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

//���_�V�F�[�_�[�̃R�A�֐��B
SPSIn VSMainCore(SVSIn vsIn, float4x4 wMat)
{
	SPSIn psIn;

	psIn.pos = mul(wMat, vsIn.pos);						//���f���̒��_�����[���h���W�n�ɕϊ��B
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	psIn.normal = normalize(mul(wMat, vsIn.normal));		//�@�������[���h���W�n�ɕϊ��B
	psIn.Tangent = normalize(mul(wMat, vsIn.Tangent));
	psIn.biNormal = normalize(mul(wMat, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// �X�L���������f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g�B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, mWorld);
}
/// <summary>
/// �X�L�������C���X�^�����f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g�B
/// </summary>
SPSIn VSMainInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
	return VSMainCore(vsIn, instancingDatas[instanceID]);
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
SPSIn VSMainSkin(SVSIn vsIn)
{
	
	SPSIn psIn;

	float4x4 m;
	m = CalcSkinMatrix(vsIn.skinVert);

	psIn.pos = mul(m, vsIn.pos);						//���f���̒��_�����[���h���W�n�ɕϊ��B
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	psIn.normal = normalize(mul(m, vsIn.normal));		//�@�������[���h���W�n�ɕϊ��B
	psIn.Tangent = normalize(mul(m, vsIn.Tangent));
	psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/*
	�X�L������C���X�^���V���O���f���p�̒��_�V�F�[�_�[�B
*/
SPSIn VSMainSkinInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SPSIn psIn;

	float4x4 m;
	m = CalcSkinMatrix(vsIn.skinVert);
	m = mul(instancingDatas[instanceID], m);

	psIn.pos = mul(m, vsIn.pos);						//���f���̒��_�����[���h���W�n�ɕϊ��B
	psIn.worldPos = psIn.pos.xyz;
	psIn.pos = mul(mView, psIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	psIn.normal = normalize(mul(m, vsIn.normal));		//�@�������[���h���W�n�ɕϊ��B
	psIn.Tangent = normalize(mul(m, vsIn.Tangent));
	psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;

	return psIn;
}

//���C�g�̋P�x�B
static const float LIGHT_LUMINANCE = float3(0.298912, 0.586611, 0.114478);

//�����x�[�X���C�e�B���O�̃s�N�Z���V�F�[�_�[�B
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//return float4(1.0f,0.0f,0.0f,1.0f);
	//�@���̌v�Z�B
	float3 normal = CalcNormal(psIn.normal,psIn.biNormal,psIn.Tangent,psIn.uv);
	float3 lig = 0;		//���C�g
	float3 toEye = normalize(eyePos - psIn.worldPos);		//�_���王�_�܂ł̐��K���x�N�g��
	float metaric = 0.0f;			//�����x�B
	float spec = 0.0f;
	float4 albedoColor = g_texture.Sample(g_sampler, psIn.uv);	//�e�N�X�`���J���[�B		
	clip(albedoColor.a - 0.1f);

	if (hasSpecularMap) {
		//�X�y�L�����}�b�v������B
		float4 specMap = g_specularMap.Sample(g_sampler, psIn.uv);
		metaric = specMap.r;
		spec = specMap.a;
	}
	float roughness = 1.0f - spec;			//�g�U���˂̖ʂ̑e���B
	//�V���h�E�B
	float4 posInView = mul(mView, float4(psIn.worldPos, 1.0f));
	float shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

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

	/*lig += albedoColor * ambientLight / PI * (1.0f - metaric);
	lig += CookTrranceSpecular(normal, toEye, normal, metaric) * albedoColor * metaric;
	*/
	//lig *= lerp(1.0f, 0.5f, shadow);

	//�ŏI�I�ȐF�����肷��B

	float4 finalColor;
	finalColor.xyz = albedoColor.xyz * lig;

	//���̌v�Z�B
	float len = length(eyePos - psIn.worldPos);
	finalColor = CalcFog(finalColor, len);

	finalColor.a = albedoColor.a;
	return finalColor;
}

//GBuffer�ɏ������ރs�N�Z���V�F�[�_�[�̃G���g���֐��B
PSOut_GBuffer PSMain_RenderGBuffer (SPSIn psIn){
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
	Out.shadow = CalcShadow(psIn.worldPos, posInView.z, isShadowReceiver);

	//���˗��B
	Out.reflection = g_reflectionMap.Sample(g_sampler, psIn.uv).xy;

	return Out;
}


/*
*	�X�L���Ȃ����f���̃V���h�E�}�b�v�������ݗp�̒��_�V�F�[�_�[�B
*/
SShadowMapPSIn VSMainNonSkinShadowMap(SShadowMapVSIn vsIn)
{
	SShadowMapPSIn psIn;
	psIn.pos = mul(mWorld, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}

/*
*	�X�L���Ȃ��C���X�^���V���O�`�惂�f���̃V���h�E�}�b�v�������ݗp�̒��_�V�F�[�_�[�B
*/
SShadowMapPSIn VSMainNonSkinInstancingShadowMap(SShadowMapVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SShadowMapPSIn psIn;
	psIn.pos = mul(instancingDatas[instanceID], vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	�X�L�����胂�f���̃V���h�E�}�b�v�������ݗp�̒��_�V�F�[�_�[�B
*/
SShadowMapPSIn VSMainSkinShadowMap(SShadowMapVSIn vsIn)
{
	SShadowMapPSIn psIn;
	float4x4 skinMatrix = CalcSkinMatrix(vsIn.skinVert);
	psIn.pos = mul(skinMatrix, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	�X�L������C���X�^���V���O�`�惂�f���̃V���h�E�}�b�v�������ݗp�̒��_�V�F�[�_�[�B
*/
SShadowMapPSIn VSMainSkinInstancingShadowMap(SShadowMapVSIn vsIn, uint instanceID : SV_InstanceID)
{
	SShadowMapPSIn psIn;
	float4x4 skinMatrix = CalcSkinMatrix(vsIn.skinVert);
	float4x4 m = instancingDatas[instanceID];
	m = mul(m, skinMatrix);

	psIn.pos = mul(m, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;

	return psIn;
}
/*
*	�V���h�E�}�b�v�������ݗp�̃s�N�Z���V�F�[�_�[�B
*/
float4 PSMainShadowMap(SShadowMapPSIn psIn) :SV_Target0
{
	float4 albedoColor = g_texture.Sample(g_sampler, psIn.uv);	//�e�N�X�`���J���[�B		
	clip(albedoColor.a - 0.1f);

	return psIn.pos.z / psIn.pos.w;
}
