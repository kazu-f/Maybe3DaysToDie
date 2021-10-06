#include "modelStruct.h"
#include "modelCB.h"
#include "CalcShadow.h"

//���f���e�N�X�`���B
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_reflectionMap : register(t3);

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

	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	Out.albedo = albedo;
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