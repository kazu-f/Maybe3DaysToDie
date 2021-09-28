/*
*	FXAA
*/

struct VSInput {
	float4 pos  : POSITION;
	float2 uv   : TEXCOORD0;
};

struct PSInput {
	float4 pos  : SV_POSITION;
	float2 uv   : TEXCOORD0;
};

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
sampler g_sampler : register(s0);

//�A���`�̏����B
float4 FxaaPixelShader(
	float2 pos,
	float4 fxaaConsoleRcpFrameOpt,
	float4 fxaaConsoleRcpFrameOpt2,
	float fxaaQualityEdgeThreshold,
	float fxaaQualityEdgeThresholdMin,
	float fxaaConsoleEdgeSharpness,
	float fxaaConsoleEdgeThreshold,
	float fxaaConsoleEdgeThresholdMin,		//�P�x�̍���臒l�̍Œ�l�B
	float2 sceneTexSize
)
{
	//�ߖT4�e�N�Z�����t�F�b�`�B
	float4 nTex = float4(
		pos.x + 0.5f / sceneTexSize.x,
		pos.y + 0.5f / sceneTexSize.y,
		pos.x - 0.5f / sceneTexSize.x,
		pos.y - 0.5f / sceneTexSize.y
		);

	float lumaNw = sceneTexture.Sample(g_sampler, nTex.xy).y;	//X+ Y+
	float lumaSw = sceneTexture.Sample(g_sampler, nTex.xw).y;	//X+ Y-
	float lumaNe = sceneTexture.Sample(g_sampler, nTex.zy).y;	//X- Y+
	float lumaSe = sceneTexture.Sample(g_sampler, nTex.zw).y;	//X- Y-

	float4 rgbyM = sceneTexture.Sample(g_sampler,pos.xy);
	float lumaM = rgbyM.y;

	//�ߖT�e�N�Z���̋P�x�̍��𒲂ׂ�B
	//Nw��Sw�̔�r�B
	float lumaMaxNwSw = max(lumaNw,lumaSw);
	lumaNe += 1.0/384.0;		//��̎��B�K�v���H
	float lumaMinNwSw = min(lumaNw,lumaSw);
	//Ne��Se�̔�r�B
	float lumaMaxNeSe = max(lumaNe,lumaSe);
	float lumaMinNeSe = min(lumaNe,lumaSe);
	//��r�������̂�����ɔ�r�B
	float lumaMax = max(lumaMaxNwSw,lumaMaxNeSe);
	float lumaMin = min(lumaMinNwSw,lumaMinNeSe);
	//�P�x�̍���臒l�B
	float lumaMaxScaled = lumaMax * fxaaConsoleEdgeThreshold;
	float lumaMaxScaledClamped = max(fxaaConsoleEdgeThresholdMin,lumaMaxScaled);	//�ŏI�I�ȋP�x�̍���臒l�B
	//�P�x�̍Œ�l�A�ő�l�B
	float lumaMinM = min(lumaMin,lumaM);		//�P�x�̍Œ�l�����߂�B
	float lumaMaxM = min(lumaMax,lumaM);		//�P�x�̍ő�l�����߂�B
	//�P�x�̍������߂�B
	float dirSwMinusNe = lumaSw - lumaNe;		//Sw - Me
	float lumaMaxSubMinM = lumaMaxM - lumaMinM;	//�ő�l - �Œ�l�B
	float dirSeMinusNw = lumaSe - lumaNw;		//Se - Nw
	//�P�x�̍���臒l�ȉ����H
	if(lumaMaxSubMinM < lumaMaxScaledClamped){
		//臒l�ȉ����������߁A�A���`�������Ȃ��B
		//return float4(0.0f, 0.0f, 0.0f, 1.0f);
		return rgbyM;
	}
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	//�P�x�̍��𗘗p���āA�M�U�M�U���������Ă���\���̍����e�N�Z�����t�F�b�`����B
	float2 dir;
	dir.x = dirSwMinusNe + dirSeMinusNw;
	dir.y = dirSwMinusNe - dirSeMinusNw;
	//dir.x = -((lumaNw + lumaNe) - (lumaSw + lumaSe));
	//dir.y = ((lumaNw + lumaSw) - (lumaNe + lumaSe));

	float2 dir1 = normalize(dir.xy);
	float4 rgbyN1 = sceneTexture.Sample(g_sampler, pos.xy - dir1 * fxaaConsoleRcpFrameOpt.zw);
	float4 rgbyP1 = sceneTexture.Sample(g_sampler, pos.xy + dir1 * fxaaConsoleRcpFrameOpt.zw);

	float dirAbsMinTimesC = min(abs(dir1.x),abs(dir1.y)) * fxaaConsoleEdgeSharpness;
	float2 dir2 = clamp(dir1.xy / dirAbsMinTimesC, -2.0, 2.0);

	float4 rgbyN2 = sceneTexture.Sample(g_sampler, pos.xy - dir2 * fxaaConsoleRcpFrameOpt2.zw);
	float4 rgbyP2 = sceneTexture.Sample(g_sampler, pos.xy + dir2 * fxaaConsoleRcpFrameOpt2.zw);
	//�u�����h
	float4 rgbyA = rgbyN1 + rgbyP1;
	//return rgbyA * 0.5f;
	float4 rgbyB = ((rgbyN2 + rgbyP2) * 0.25) + (rgbyA * 0.25);

	int twoTap = (rgbyB.y < lumaMin) || (rgbyB.y > lumaMax);

	if(twoTap){
		//�P�x�̍����܂��傫�����߃u�����h�B
		rgbyB.xyz = rgbyA.xyz * 0.5;

		//return float4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	return rgbyB;
}

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain(PSInput In) : SV_TARGET0
{
	float2 texSize;
	float level;
	sceneTexture.GetDimensions(0, texSize.x, texSize.y, level);	//�e�N�X�`���̃T�C�Y���擾�B
	float4 rcpFrame = float4(0.0f, 0.0f, 1.0f/texSize.x, 1.0f/texSize.y);
	return FxaaPixelShader(
		In.uv,
		rcpFrame,			//fxaaConsoleRcpFrameOpt
		rcpFrame,			//fxaaConsoleRcpFrameOpt2
		0.166f,				//fxaaQualityEdgeThreshold
		0.0833f,			//fxaaQualityEdgeThresholdMin
		1.0f,				//fxaaConsoleEdgeSharpness
		0.4f,				//fxaaConsoleEdgeThreshold
		0.0833f,			//fxaaConsoleEdgeThresholdMin
		texSize				//�e�N�X�`���̃T�C�Y�B
	);

	//return FxaaPixelShader(
	//	In.uv,
	//	rcpFrame,			//fxaaConsoleRcpFrameOpt
	//	rcpFrame,			//fxaaConsoleRcpFrameOpt2
	//	0.166f,				//fxaaQualityEdgeThreshold
	//	0.0833f,			//fxaaQualityEdgeThresholdMin
	//	1.0f,				//fxaaConsoleEdgeSharpness
	//	0.125,				//fxaaConsoleEdgeThreshold
	//	0.0312,			//fxaaConsoleEdgeThresholdMin
	//	texSize				//�e�N�X�`���̃T�C�Y�B
	//);
}


