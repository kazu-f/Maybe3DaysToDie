#include "stdafx.h"
#include "GameScene.h"
#include "Scene\TerrainDebugScene.h"

//1�t���[���̌o�ߎ��Ԃ��o�͂���B
#define CALC_TIME

LRESULT  CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);

 MauseState g_MauseState= MauseState::None;

LRESULT  CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC         hdc;
	PAINTSTRUCT ps;
	float x = 0.0f;
	float y = 0.0f;
	//�n���ꂽ message ����A�C�x���g�̎�ނ���͂���
	switch (msg) {
	case WM_CREATE:
		x = 50;
		y = 50;
		break;
	case WM_LBUTTONDOWN:
		g_MauseState = MauseState::LBotunClick;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);  //�̈斳����
		break;
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);  //�̈斳����
		break;
		//----�y�C���g----
	case WM_PAINT:
		break;
		//----�I������----
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0L;
	}
	//�f�t�H���g�̏���
	return  DefWindowProc(hWnd, msg, wParam, lParam);
}
void SetInitParam(SInitParam& initParam)
{
	initParam.frameBuffer_W = FRAME_BUFFER_W;	//�t���[���o�b�t�@�̃T�C�Y(��)
	initParam.frameBuffer_H = FRAME_BUFFER_H;	//�t���[���o�b�t�@�̃T�C�Y(����)
	initParam.gameObjectPrioMax = 20;			//�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B

	initParam.graphicsConf.shadowConf.isEnable = true;		//�V���h�E�}�b�v�̗L�����t���O�B
	initParam.graphicsConf.shadowConf.shadowMapWidth = 4096;
	initParam.graphicsConf.shadowConf.shadowMapWidth = 4096;
	initParam.graphicsConf.shadowConf.shadowAreas[0] = 2000.0f;		//�V���h�E�}�b�v�̗L���͈�(�ߌi)
	initParam.graphicsConf.shadowConf.shadowAreas[1] = 4000.0f;		//�V���h�E�}�b�v�̗L���͈�(���i)
	initParam.graphicsConf.shadowConf.shadowAreas[2] = 20000.0f;	//�V���h�E�}�b�v�̗L���͈�(���i)
	//initParam.graphicsConf.shadowConf.depthOffset[0] = 0.01f;
	//initParam.graphicsConf.shadowConf.depthOffset[1] = 0.02f;
	//initParam.graphicsConf.shadowConf.depthOffset[2] = 0.02f;
	initParam.graphicsConf.shadowConf.lightHeight = 5000.0f;
	initParam.graphicsConf.postEffectConf.tonemap.isEnable = false;		//�g�[���}�b�v�L�����t���O�B
	initParam.graphicsConf.postEffectConf.tonemap.luminance = 0.24f;	//���邳�B
	initParam.graphicsConf.postEffectConf.isBloom = true;	//�u���[���̗L�����t���O�B
	initParam.graphicsConf.postEffectConf.isFxaa = true;	//�A���`�G�C���A�X�L�����t���O�B
}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	SInitParam initParam;
	SetInitParam(initParam);
	WNDCLASS wc = { CS_CLASSDC,
				   WndProc,                               //�C�x���gcallback�֐�
				   0L,
				   0L,
				   hInstance,
				   NULL,                                  //�A�C�R��
				   LoadCursor(NULL,IDC_ARROW),            //�}�E�X�J�[�\��
				   (HBRUSH)GetStockObject(WHITE_BRUSH),
				   NULL,
				   TEXT("Game")
	};
	if (RegisterClass(&wc) == 0) return FALSE;

	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"), initParam);
	//�f�o�b�O���[�h�I��
	//PhysicsWorld().SetDebugMode(1);
	//�t�F�[�h�C��
	CFade::GetInstance()->StartFadeIn();
	//�}�E�X�J�[�\���̕\��������
	ShowCursor(false);

	NewGO<CGameScene>(0);
	//NewGO<TerrainDebugScene>(0);
#ifdef CALC_TIME
	Stopwatch sw;
#endif
	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
#ifdef CALC_TIME
		//1�t���[���̌o�ߎ��Ԃ𑪂�B
		sw.Start();
#endif
		GameEngine().GameUpdate();

#ifdef CALC_TIME
		sw.Stop();
#endif
		
#ifdef CALC_TIME
		char text[256];
		sprintf_s(text, "1�t���[���̌o�ߎ���::%d�~���b\n", static_cast<int>(sw.GetElapsedMillisecond()));
		OutputDebugString(text);
#endif

	}
	return 0;
}


