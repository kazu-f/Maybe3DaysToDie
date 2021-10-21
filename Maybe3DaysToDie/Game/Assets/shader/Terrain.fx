
//�n�`�p�̒萔�o�b�t�@
cbuffer ModelCb : register(b0) {
	float4x4 mView			: packoffset(c0);
	float4x4 mProj			: packoffset(c4);
};

//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn {
	float4 pos : POSITION;		//�n�`�̒��_���W�B
	float2 uv : TEXCOORD0;	//UV���W�B
};

struct SPSIn {
	float4 pos : SV_POSITION;	//�X�N���[����Ԃł̃s�N�Z���̍��W�B
	float2 uv : TEXCOORD0;	//UV���W�B
};

Texture2D<float4> g_albedoMap : register(t0);	//�A���x�h

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
	psIn.uv = vsIn.uv;

	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedoMap.Sample(g_sampler, psIn.uv);		//�A���x�h�B
	albedoColor.a = 1.0f;

	return albedoColor;
}

