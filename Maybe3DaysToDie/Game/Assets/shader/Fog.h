/*
*	�t�H�O�B
*/

static const float FOG_START	=  40000.0f;		//�t�H�O���|����n�߂鋗���B
static const float FOG_END		= 80000.0f;		//�t�H�O�����S�Ɋ|���鋗���B
static const float4 FOG_COLOR = float4(0.6f, 0.6f, 0.6f, 1.0f);		//�t�H�O�̐F�B

float4 CalcFog(float4 color, float dist)
{
	float fog = (FOG_END - dist) / (FOG_END - FOG_START);
	fog = max(0.0f, min(1.0f, fog));
	fog = pow(fog, 1.0f);
	float4 finalColor = color * fog + FOG_COLOR * (1.0f - fog);
	return finalColor;
}

/*
*	�X�J�C�L���[�u�p�̃t�H�O�B
*/

static const float SKYFOG_START	= 2500.0f;		//�t�H�O���J�n���鍂���B
static const float SKYFOG_END	= 100.0f;		//�t�H�O�����S�Ɋ|���鍂���B

float4 CalcSkyFog(float4 color, float height)
{
	float fog = (SKYFOG_END - abs(height)) / (SKYFOG_END - SKYFOG_START);
	fog = max(0.0f, min(1.0f, fog));

	float4 finalColor = color * fog + FOG_COLOR * (1.0f - fog);
	return finalColor;
}


