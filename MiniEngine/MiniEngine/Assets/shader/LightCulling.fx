/*
*	���C�g�J�����O�B
*/

// ��x�Ɏ��s�����X���b�h��
static const int TILE_WIDTH = 16;		//�^�C���̕�
static const int TILE_HEIGHT = 16;		//�^�C���̍���

// �^�C���̑���
static const int TILE_SIZE = (TILE_WIDTH * TILE_HEIGHT);

#include "LightStruct.h"

cbuffer cbCameraParam : register(b0)
{
    float4x4 mtxProj : packoffset(c0);      // ���e�s��
    float4x4 mtxProjInv : packoffset(c4);   //  ���e�s��̋t�s��
    float4x4 mtxViewRot : packoffset(c8);
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
	float4 screenParam		: packoffset(c2);		//�X�N���[���p�����[�^(near,far,screenW,screenH)
}

// ����
// �[�x�e�N�X�`��
Texture2D depthTexture : register(t0);

StructuredBuffer<SPointLight> g_pointLight : register(t0);

// �o�͗p�̃o�b�t�@�[
RWStructuredBuffer<uint> rwLightIndices : register(u0); // ���C�g�C���f�b�N�X�o�b�t�@�[

groupshared uint sMinZ;		//�^�C���̍ŏ��[�x�B
groupshared uint sMaxZ;		//�^�C���̍ő�[�x�B
groupshared uint sTileLightIndices[MAX_POINT_LIGHT];		//�^�C���ɐڐG���Ă���|�C���g���C�g�̃C���f�b�N�X�B
groupshared uint sTileNumLights;		//�^�C���ɐڐG���Ă���|�C���g���C�g�̐��B

/*
*	�^�C�����Ƃ̎����䕽�ʂ����߂�B
*/
void GetTileFrustumPlane(out float4 frustumPlanes[6], uint3 groupId)
{
	//�^�C���̍ő�E�ŏ��[�x�𕂓������_�ɕϊ�
	float minTileZ = asfloat(sMinZ);
	float maxTileZ = asfloat(sMaxZ);

	float2 tileScale = screenParam.zw * rcp(float(2 * TILE_WIDTH));
	float2 tileBias = tileScale - float2(groupId.xy);

	float4 c1 = float4(mtxProj._11 * tileScale.x, 0.0f, tileBias.x, 0.0f);
	float4 c2 = float4(0.0f, -mtxProj._22 * tileScale.y, tileBias.y, 0.0f);
	float4 c4 = float4(0.0f, 0.0f, 1.0f, 0.0f);

	//���ʂ̕��������߂�B
	frustumPlanes[0] = c4 - c1;		//Right
	frustumPlanes[1] = c4 + c1;		//Left
	frustumPlanes[2] = c4 - c2;		//Top
	frustumPlanes[3] = c4 + c2;		//Bottom
	frustumPlanes[4] = float4(0.0f, 0.0f, 1.0f, -minTileZ);
	frustumPlanes[5] = float4(0.0f, 0.0f, 1.0f, maxTileZ);

	//�@���̐��K���B
	for (uint i = 0; i < 4; ++i)
	{
		frustumPlanes[i] *= rcp(length(frustumPlanes[i].xyz));
	}
}

/*
* �J������Ԃł̍��W���v�Z����B
*/
float3 ComputePositionInCamera(uint2 globalCoords)
{
	float2 st = ((float2)globalCoords + 0.5f) * rcp(screenParam.zw);
	st = st * float2(2.0f, -2.0f) - float2(1.0f, -1.0f);
	float3 screenPos;
	screenPos.xy = st.xy;
	screenPos.z = depthTexture.Load(uint3(globalCoords, 0.0f));
	float4 cameraPos = mul(mtxProjInv, float4(screenPos, 1.0f));

	return cameraPos.xyz / cameraPos.w;
}

/*
* CSMain ���C�g�J�����O�̃R���s���[�g�V�F�[�_�[�B
*/
[numthreads(TILE_WIDTH,TILE_HEIGHT,1)]
void CSMain(
	uint3 groupId			: SV_GroupID,
	uint3 dispatchThreadId : SV_DispatchThreadID,
	uint3 groupThreadId : SV_GroupThreadID)
{
	//�^�C�����ł̃C���f�b�N�X�����߂�B
	uint groupIndex = groupThreadId.y * TILE_WIDTH + groupThreadId.x;
	//0�Ԗڂ̃X���b�h�ŋ��L�������������B
	if (groupIndex == 0)
	{
		sTileNumLights = 0;
		sMinZ = 0x7F7FFFFF;	//float�̍ő�l�B
		sMaxZ = 0;
	}
	//���̃X���b�h���S������s�N�Z���̃J������Ԃł̍��W���v�Z�B
	uint2 frameUV = dispathcThreadId.xy;
	//�r���[��Ԃł̍��W���v�Z�B
	float3 posInView = ComputePositionInCamera(frameUV);

	//���L�������̏�������ۏ؂��铯���B
	GroupMemoryBarrierWithGroupSync();

	//�^�C���̍ő�E�ŏ��[�x�����߂�B
	InterlockedMin(sMinZ, asuint(posInView.z));
	InterlockedMax(sMaxZ, asuint(posInView.z));

	//�^�C���̍ő�E�ŏ��[�x�𐳊m�ɂ��铯���B
	GroupMemoryBarrierWithGroupSync();

	//�^�C���̎�������\������6�̕��ʂ����߂�B
	float4 frustumPlanes[6];
	GetTileFrustumPlane(frustumPlanes, groupId);

	//�^�C���ƃ|�C���g���C�g�̏Փ˔�������B
	for (uint lightIndex = groupIndex;
		lightIndex < numPointLight;
		lightIndex += TILE_SIZE)
	{
		SPointLight light = g_pointLight[lightIndex];

		//�^�C���Ƃ̔���B
		bool inFrustum = ture;
		for (uint i = 0; i < 6; ++i)
		{
			//���C�g�̍��W�ƕ��ʂ̖@���Ƃœ��ς��g���āA���C�g���ʂƂ̋������v�Z�B
			float4 lp = float4(light.positionInView, 1.0f);
			float d = dot(frustumPlanes[i], lp);
			//���C�g�ƕ��ʂ̋������g���āA�Փ˔�����s���Ă���B
			inFrustum = inFrustum && (d >= -light.range);
		}

		//�^�C���ƏՓ˂��Ă���ꍇ
		if (inFrustum)
		{
			//�Փ˂����|�C���g���C�g�̔ԍ����e�����X�g�ɐς�ł����B
			uint listIndex;
			InterlockedAdd(sTileNumLights, 1, listIndex);
			sTileLightIndices[listIndex] = lightIndex;
		}
	}
	//sTileLightIndices�Ƀ��C�g�C���f�b�N�X���ςݐ؂��Ă��铯�������B
	GroupMemoryBarrierWithGroupSync();

	//���C�g�C���f�b�N�X���o�̓o�b�t�@�[�ɏo��
	uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
	uint tileIndex = floor(frameUV.x / TILE_WIDTH) + floor(frameUV.y / TILE_WIDTH) * numCellX;
	uint lightStart = numPointLight * tileIndex;
	for (uint lightIndex = groupIndex; lightIndex < sTileNumLights; lightIndex += TILE_SIZE)
	{
		rwLightIndices[lightStart + lightIndex] = sTileLightIndices[lightIndex];
	}

	//�ԕ���ݒ�B
	if ((groupIndex == 0) && (sTileNumLights < numPointLight))
	{
		//-1�Ŕԕ��B
		rwLightIndices[lightStart + sTileNumLights] = 0xffffffff;
	}

}

