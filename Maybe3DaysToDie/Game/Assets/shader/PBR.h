
//�~�����B
static const float PI = 3.14159265358979323846;

//�x�b�N�}�����z?	
//���̕��U������߂�H
/*
	m			(�ʂ̑e��)
	t = N�EH	(�@���E�n�[�t�x�N�g��)
	M = m^2		T = (N�EH)^2
*/
float Beckmann(float m, float t)
{

	float t2 = t * t;
	float t4 = t * t * t * t;
	float m2 = m * m;
	float D = 1.0f / (4.0f * m2 * t4);
	D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
	return D;

	//float M = m;
	//float T = t * t;
	//return exp((T - 1) / (M * T)) / (PI * M * T * T);
}

//�t���l����?�̋ߎ����炵���H
float specFresnel(float f0, float u)
{
	//�������˂̂���f90��1.0�Œ�ł����B
	return f0 + (1.0f - f0) * pow(1.0f - u, 5);
}

/*
*	�N�b�N�g�����X���f���̋��ʔ��˂��v�Z�B
*	�X�y�L�����̌v�Z�Ɏg���Ă�B�H
*	L�����C�g
*	V�����_
*	N���@��
*/
float CookTrranceSpecular(float3 L, float3 V, float3 N, float metaric)
{
	float microfacet = max(0.18f, 1.0f - metaric);		//�}�C�N���t�@�Z�b�g
									//�\�ʂ̓ʉ����\���I�ȁH
									//�ʂ̑e���Ƃ��𒲐�����p�����[�^�炵���H
	float f0 = metaric;				//�������ˎ��̃t���l�����ˌW���B

	float3 H = normalize(L + V);		//���C�g+���_�̃n�[�t�x�N�g���B

	//�F�X���ώ���Ă�B
	float NdotH = saturate(dot(N, H));		//�@���ƃn�[�t�x�N�g��
	float VdotH = saturate(dot(V, H));		//���_�ƃn�[�t�x�N�g��
	float NdotL = saturate(dot(N, L));		//�@���ƃ��C�g
	float NdotV = saturate(dot(N, V));		//�@���Ǝ��_

	float D = Beckmann(microfacet, NdotH);	//�����ʕ��z�֐��B
	float F = specFresnel(f0, VdotH);		//�t���l�����B

	float t = 2.0 * NdotH / VdotH;			//�v�Z�̋��ʍ�������Ă��������B
	float G = min(1.0f, min(t * NdotV, t * NdotL));		//�􉽊w�I�����W���H
																	//�ő�l��1.0�A�ŏ��l��0.0�̊Ԃ�
																	//�l�̏������ق������

	float m = PI * max(NdotV * NdotL,0.01f);			//�N�b�N�g�����X���˃��f���̕���ɂȂ�l�H	

	/*
	*	F:�t���l����
	*	D:�����ʕ��z
	*	G:�􉽊w�I�����W��
	*/
	return max(F * D * G / m, 0.0f);
}

/*
*	�t���l�����̋ߎ����B
*	f0�������Ɍ������˂����Ƃ��̃t���l�����˗��B
*	f90�����s�Ɍ������˂����Ƃ��̃t���l�����˗��B
*/
float SchlickFresnel(float u, float f0, float f90)
{
	return f0 + (f90 - f0) * pow(1.0f - u, 5.0f);
}

/*
*	���K��Disney���f���g�U���ˁB
*	albedColor	:	���C�g�̋������H
*	N			:	�@���̐��K���x�N�g��
*	L			:	���C�g�ւ̐��K���x�N�g��
*	V			:	���_�̐��K���x�N�g��
*	roughness	:	�\�ʂ̑e����\���p�����[�^�炵��
*/
float NormalizedDisneyDiffuse(float3 N, float3 L, float3 V, float roughness)
{
	////�@���ƃ��C�g�����̓��ρB
	//float dotNL = saturate(dot(N, L));
	////�@���Ǝ��_�����̓��ρB
	//float dotNV = saturate(dot(N, V));

	//return max(0.2f, dotNL * dotNV);

	float3 H = normalize(L + V);		//�n�[�t�x�N�g���B

	float energyBias = lerp(0.0f, 0.5f, roughness);				//�Ȃ񂩐��K���̂��߂̐��l�H0.0�`0.5�̐��`�⊮
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
	//���ς���B(����0.0�`���1.0)
	float LdotH = saturate(dot(L, H));		//���C�g�ƃn�[�t�x�N�g��
	float NdotL = saturate(dot(N, L));		//�@���ƃ��C�g
	float NdotV = saturate(dot(N, V));		//�@���Ǝ��_
	float HdotV = saturate(dot(H, V));		//�n�[�t�x�N�g���Ǝ��_

	//�䐔�l�@�t���l�����˗�?(0.0�`1.0)
	//�������s�ɓ��˂����Ƃ��̃t���l�����˗������߂�B
	float Fd90 = energyBias + 2.0f * LdotH * LdotH * roughness;

	float FL = SchlickFresnel(NdotL, 1.0f, Fd90);	//�t���l���W��(�@���E���C�g)
	float FV = SchlickFresnel(NdotV, 1.0f, Fd90);	//�t���l���W��(�@���E���_)

	/*
	*	�t���l���W��(N�EL) * �t���l���W��(N�EV)
	*	����𐳋K�������o�[�g�g�U�֊|����B
	*/
	return (FL * FV * energyFactor);
}