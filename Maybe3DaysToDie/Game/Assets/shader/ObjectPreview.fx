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
float4 PSMain(SPSIn psIn) :SV_Target0
{
	//�A���x�h
	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);
	//�������ɂ���
	albedo.a = 0.75f;

	return albedo;
}