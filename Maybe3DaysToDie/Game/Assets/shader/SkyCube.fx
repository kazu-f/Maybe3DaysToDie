/*
*	�X�J�C�L���[�u�V�F�[�_�[�B
*/

#include "modelCB.h"
#include "Fog.h"

TextureCube<float4> skyCubeMap : register(t0);		//�X�J�C�L���[�u�}�b�v�B

//�T���v���X�e�[�g�B
sampler g_sampler : register(s0);

//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn_SkyCube {
	float4 pos : POSITION;		//���f���̒��_���W�B
	float3 normal : NORMAL;		//�@���B
};

struct SPSIn_SkyCube {
	float4 pos : SV_POSITION;	//�X�N���[����Ԃł̃s�N�Z���̍��W�B
	float3 normal : NORMAL;		//�@���B
	float3 worldPos : TEXCODE0;	//���[���h���W�B
};

//��p�̒��_�V�F�[�_�[�B
SPSIn_SkyCube VSMain_SkyCube(SVSIn_SkyCube In) {
	SPSIn_SkyCube psIn;

	psIn.pos = mul(mWorld, In.pos);						//���f���̒��_�����[���h���W�n�ɕϊ��B
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);						//���[���h���W�n����J�������W�n�ɕϊ��B
	psIn.pos = mul(mProj, psIn.pos);						//�J�������W�n����X�N���[�����W�n�ɕϊ��B
	//psIn.normal = In.normal;								//�@���B
	psIn.normal = normalize(mul(mWorld, In.normal));		//�@�������[���h���W�n�ɕϊ��B

	return psIn;
}

//��p�̃s�N�Z���V�F�[�_�[�B
float4 PSMain_SkyCube(SPSIn_SkyCube In) : SV_Target0
{
	float4 color;	
	color.xyz = skyCubeMap.Sample(g_sampler, In.normal).xyz;
	color.xyz += emissionColor;

	color = CalcSkyFog(color, In.worldPos.y);
	color.a = 1.0f;

	return color;
	//return float4(1.0f,0.0f,0.0f,1.0f);
}
