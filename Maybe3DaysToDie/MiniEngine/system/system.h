#pragma once
namespace Engine {
	class CGraphicsEngine;
	struct SInitParam;
	extern HWND			g_hWnd;				//�E�B���h�E�n���h���B

	//�Q�[���̏������B
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName, const SInitParam& initParam);
	//�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
	bool DispatchWindowMessage();
}