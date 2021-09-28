/*
*	�g�[���}�b�v�B
*/

struct VSInput {
	float4 pos  : POSITION;
	float2 uv   : TEXCOORD0;
};

struct PSInput {
	float4 pos  : SV_POSITION;
	float2 uv   : TEXCOORD0;
};

//�g�[���}�b�v�̋��ʒ萔�o�b�t�@�B
cbuffer cbTonemapCommon : register(b1) {
	float deltaTime;
	float middleGray;
};

/*
*	���_�V�F�[�_�[�B
*/
PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

Texture2D<float4> sceneTexture : register(t0);		//�V�[���e�N�X�`���B
sampler Sampler : register(s0);

//�P�x�̑ΐ����ς����߂�B

static const float3 LUMINANCE_VECTOR = float3(0.2125f, 0.7154f, 0.0721f);
static const int MAX_SAMPLES = 16;

/*
*	�萔�o�b�t�@�B
*/
cbuffer cbCalcLuminanceLog : register(b0) {
	float4 g_avSampleOffsets[MAX_SAMPLES];
};

/*
*	�P�x�̑ΐ����ς����߂�B
*/
float4 PSCalcLuminanceLogAverage(PSInput In) : SV_TARGET0
{
	//return sceneTexture.Sample(Sampler,In.uv);

	float3 vSampler = 0.0f;
	float fLogLumSum = 0.0f;

	for (int iSample = 0; iSample < 9; iSample++)
	{
		vSampler = sceneTexture.Sample(Sampler, In.uv + g_avSampleOffsets[iSample].xy);
		//float d = max(dot(vSampler, LUMINANCE_VECTOR),0.0f) + 0.0001f;
		float d = dot(vSampler, LUMINANCE_VECTOR) + 0.0001f;
		fLogLumSum += log(d);
	}
	
	fLogLumSum /= 9;

	return float4(fLogLumSum, fLogLumSum, fLogLumSum, 1.0f);
}

/*
*	���ϋP�x�v�Z�s�N�Z���V�F�[�_�[�B
*/
float4 PSCalcLuminanceAverage(PSInput In) : SV_TARGET0
{

	float fResampleSum = 0.0f;
	
	for (int iSample = 0; iSample < 16; iSample++) 
	{
		fResampleSum += sceneTexture.Sample(Sampler, In.uv + g_avSampleOffsets[iSample].xy);
	}

	fResampleSum /= 16;

	return float4(fResampleSum, fResampleSum, fResampleSum, 1.0f);
}

/*
*	�w���֐����g�p���ĕ��ϋP�x�����߂�s�N�Z���V�F�[�_�[�B
*/
float4 PSCalcLuminanceExpAverage(PSInput In) : SV_TARGET0
{
	float fResampleSum = 0.0f;
	
	for (int iSample = 0; iSample < 16; iSample++)
	{
		fResampleSum += sceneTexture.Sample(Sampler, In.uv + g_avSampleOffsets[iSample].xy);
	}

	//fResampleSum = max(0.5f,exp(fResampleSum / 16));
	fResampleSum = exp(fResampleSum / 16);

	return float4(fResampleSum, fResampleSum, fResampleSum, 1.0f);
}

/*
*	���Ï����B
*/

Texture2D<float4> lumAvgTexture : register(t1);		//���ϋP�x�B
Texture2D<float4> lastLumAvgTexture : register(t2);	//��t���[���O�̕��ϋP�x�B

/*
*	���Ï����̂��߂̕��ϋP�x�̓K��������s�N�Z���V�F�[�_�[�B
*/
float4 PSCalcAdaptedLuminance(PSInput In) : SV_TARGET0
{
	float fAdaptedLum = lastLumAvgTexture.Sample(Sampler,float2(0.5f,0.5f));
	float fCurrentLum = lumAvgTexture.Sample(Sampler,float2(0.5f,0.5f));

	float fNewAdaptation = fAdaptedLum + (fCurrentLum - fAdaptedLum) * ( 1 - pow(0.98f,60*deltaTime));
	
	return float4(fNewAdaptation,fNewAdaptation,fNewAdaptation,1.0f);
}
/*
*	���Ï����̂��߂̃s�N�Z���V�F�[�_�[�B(�V�[�����؂�ւ�������Ɏg�p����B)
*/
float4 PSCalcAdaptedLuminanceFirst(PSInput In):SV_TARGET0
{
	float fAvgLum = lumAvgTexture.Sample(Sampler,float2(0.5f,0.5f));
	return float4(fAvgLum,fAvgLum,fAvgLum,1.0f);
}

float3 Rgb2Hsv(float3 rgb) 
{
	float3 hsv;
	// RGB 2 HSV
	float fmax = max(rgb.r, max(rgb.g, rgb.b));
	float fmin = min(rgb.r, min(rgb.g, rgb.b));
	float delta = fmax - fmin;
	hsv.z = fmax; // v
	if (fmax != 0.0) {
		hsv.y = delta / fmax;//s
	}
	else {
		hsv.y = 0.0;//s
	}
	if (rgb.r == fmax) {
		hsv.x = (rgb.g - rgb.b) / delta;// h
	}
	else if (rgb.g == fmax) {
		hsv.x = 2 + (rgb.b - rgb.r) / delta;// h
	}
	else {
		hsv.x = 4 + (rgb.r - rgb.g) / delta;// h
	}
	hsv.x /= 6.0;
	if (hsv.x < 0) hsv.x += 1.0;
	
	return hsv;
}
float3 Hsv2Rgb(float3 hsv)
{
	float3 ret;
	// HSV 2 RGB
	if (hsv.y == 0) { /* Grayscale */
		ret.r = ret.g = ret.b = hsv.z;// v
	}
	else {
		if (1.0 <= hsv.x) hsv.x -= 1.0;
		hsv.x *= 6.0;
		float i = floor(hsv.x);
		float f = hsv.x - i;
		float aa = hsv.z * (1 - hsv.y);
		float bb = hsv.z * (1 - (hsv.y * f));
		float cc = hsv.z * (1 - (hsv.y * (1 - f)));
		if (i < 1) {
			ret.r = hsv.z; ret.g = cc;    ret.b = aa;
			
		}
		else if (i < 2) {
			ret.r = bb;    ret.g = hsv.z; ret.b = aa;
		}
		else if (i < 3) {
			ret.r = aa;    ret.g = hsv.z; ret.b = cc;
		}
		else if (i < 4) {
			ret.r = aa;    ret.g = bb;    ret.b = hsv.z;
		}
		else if (i < 5) {
			ret.r = cc;    ret.g = aa;    ret.b = hsv.z;
		}
		else {
			ret.r = hsv.z; ret.g = aa;    ret.b = bb;
		}
	}
	return ret;
}
/*
*	���ϋP�x����g�[���}�b�v���s���s�N�Z���V�F�[�_�[�B
*/
float4 PSFinal(PSInput In) : SV_TARGET0
{
	float4 vSample = sceneTexture.Sample(Sampler,In.uv);
	float fAvgLum = lumAvgTexture.Sample(Sampler,float2(0.5f,0.5f)).r;
	//float3 hsv = Rgb2Hsv(vSample.xyz);
	//hsv.z *= middleGray / max(0.0001f,fAvgLum);
	//hsv.z -= fAvgLum;
	//hsv.z += middleGray;
	//hsv.z = max(0.0f, hsv.z);
	//vSample.xyz = Hsv2Rgb(hsv);
	/*float3 avgColor = LUMINANCE_VECTOR * fAvgLum;
	//���σJ���[�Ƃ̍������v�Z����B
	vSample.xyz = vSample.xyz - avgColor;
	vSample.xyz += LUMINANCE_VECTOR * 0.5f;
	vSample.xyz = max(float3(0.0f, 0.0f, 0.0f), vSample.xyz);
	*/
	//���ϋP�x����ʂ̒��S�̖��邳�Ƃ��čČv�Z���s���B
	//float t = dot(LUMINANCE_VECTOR, vSample);
	vSample.rgb *= middleGray / max(0.0001f,fAvgLum);
	//vSample.rgb /= (1.0f+vSample);
	return vSample;
}

