#include "MiniEngine.h"
#include "system.h"
#include "graphics/GraphicsEngine.h"
#include "Mause/MauseInfo.h"
namespace Engine {
	HWND			g_hWnd = NULL;				//�E�B���h�E�n���h���B

	///////////////////////////////////////////////////////////////////
	//���b�Z�[�W�v���V�[�W���B
	//hWnd�����b�Z�[�W�𑗂��Ă����E�B���h�E�̃n���h���B
	//msg�����b�Z�[�W�̎�ށB
	//wParam��lParam�͈����B���͋C�ɂ��Ȃ��Ă悢�B
	///////////////////////////////////////////////////////////////////
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (wParam > 0) {
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseWheelUp);
		}
		if (wParam < 0) {
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseWheelDown);
		}
		//�����Ă������b�Z�[�W�ŏ����𕪊򂳂���B
		switch (msg)
		{
		case WM_DESTROY:
			//�G���W���̔j���B
			GameEngine().Release();
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(g_hWnd);
				break;
			default:
				break;
			}
			//�n���ꂽ message ����A�C�x���g�̎�ނ���͂���
		case WM_LBUTTONDOWN:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseLClick);
			break;
		case WM_RBUTTONDOWN:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::MauseRClick);
			break;
		default:
			MauseInfo::GetInstance()->SetMauseState(MauseInfo::State::None);
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return 0;
	}


	///////////////////////////////////////////////////////////////////
	// �E�B���h�E�̏������B
	///////////////////////////////////////////////////////////////////
	void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName)
	{
		//�E�B���h�E�N���X�̃p�����[�^��ݒ�(�P�Ȃ�\���̂̕ϐ��̏������ł��B)
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),		//�\���̂̃T�C�Y�B
			CS_CLASSDC,				//�E�B���h�E�̃X�^�C���B
									//�����̎w��ŃX�N���[���o�[��������ł��邪�A�Q�[���ł͕s�v�Ȃ̂�CS_CLASSDC�ł悢�B
			MsgProc,				//���b�Z�[�W�v���V�[�W��(��q)
			0,						//0�ł����B
			0,						//0�ł����B
			GetModuleHandle(NULL),	//���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h���B
									//�����C�ɂ��Ȃ��Ă悢�B
			NULL,					//�A�C�R���̃n���h���B�A�C�R����ς������ꍇ������ύX����B�Ƃ肠��������ł����B
			NULL,					//�}�E�X�J�[�\���̃n���h���BNULL�̏ꍇ�̓f�t�H���g�B
			NULL,					//�E�B���h�E�̔w�i�F�BNULL�̏ꍇ�̓f�t�H���g�B
			NULL,					//���j���[���BNULL�ł����B
			appName,				//�E�B���h�E�N���X�ɕt���閼�O�B
			NULL					//NULL�ł����B
		};
		//�E�B���h�E�N���X�̓o�^�B
		RegisterClassEx(&wc);

		// �E�B���h�E�̍쐬�B
		g_hWnd = CreateWindow(
			appName,				//�g�p����E�B���h�E�N���X�̖��O�B
									//��قǍ쐬�����E�B���h�E�N���X�Ɠ������O�ɂ���B
			appName,				//�E�B���h�E�̖��O�B�E�B���h�E�N���X�̖��O�ƕʖ��ł��悢�B
			WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C���B�Q�[���ł͊�{�I��WS_OVERLAPPEDWINDOW�ł����A
			0,						//�E�B���h�E�̏���X���W�B
			0,						//�E�B���h�E�̏���Y���W�B
			FRAME_BUFFER_W,			//�E�B���h�E�̕��B
			FRAME_BUFFER_H,			//�E�B���h�E�̍����B
			NULL,					//�e�E�B���h�E�B�Q�[���ł͊�{�I��NULL�ł����B
			NULL,					//���j���[�B����NULL�ł����B
			hInstance,				//�A�v���P�[�V�����̃C���X�^���X�B
			NULL
		);

		ShowWindow(g_hWnd, nCmdShow);

	}


	//�Q�[���̏������B
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName, const SInitParam& initParam)
	{
		MauseInfo::Create();
		//�E�B���h�E���������B
		InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, appName);
		//�G���W���̃C���X�^���X���쐬�B
		TkEngine::CreateInstance();
		//TK�G���W���̏������B
		GameEngine().Init(g_hWnd, initParam);
	}
	//�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
	bool DispatchWindowMessage()
	{
		MSG msg = { 0 };
		while (WM_QUIT != msg.message) {
			//�E�B���h�E����̃��b�Z�[�W���󂯎��B
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				//�E�B���h�E���b�Z�[�W����ɂȂ����B
				break;
			}
		}
		return msg.message != WM_QUIT;
	}
}