#include "GBufferStruct.h"

//�X�L�j���O�p�̒��_�f�[�^���ЂƂ܂Ƃ߁B
struct SSkinVSIn {
	int4  Indices : BLENDINDICES0;
	float4 Weights : BLENDWEIGHT0;
};

//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn {
	float4 pos : POSITION;		//���f���̒��_���W�B
	float3 normal : NORMAL;		//�@���B
	float3 Tangent : TANGENT;	//�@���ɑ΂��ĉ��H�ɐ����ȃx�N�g���B
	float3 biNormal : BINORMAL;	//�]�@���B�@���ɑ΂��ď�H�ɐ����ȃx�N�g���B
	float2 uv : TEXCOORD0;	//UV���W�B
	SSkinVSIn skinVert;				//�X�L���p�̒��_�f�[�^�B
};

//�s�N�Z���V�F�[�_�[�ւ̓��́B
struct SPSIn {
	float4 pos : SV_POSITION;	//�X�N���[����Ԃł̃s�N�Z���̍��W�B
	float3 normal : NORMAL;		//�@���B
	float3 Tangent : TANGENT;	//
	float3 biNormal : BINORMAL;	//�]�@���B
	float2 uv : TEXCOORD0;	//uv���W�B
	float3 worldPos : TEXCOORD1;	//���[���h��Ԃł̃s�N�Z���̍��W�B
};

//�V���h�E�}�b�v�p�̒��_�V�F�[�_�[�ւ̓��́B
struct SShadowMapVSIn {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;	//uv���W�B
	SSkinVSIn skinVert;
};

//�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��́B
struct SShadowMapPSIn {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;	//uv���W�B
};

