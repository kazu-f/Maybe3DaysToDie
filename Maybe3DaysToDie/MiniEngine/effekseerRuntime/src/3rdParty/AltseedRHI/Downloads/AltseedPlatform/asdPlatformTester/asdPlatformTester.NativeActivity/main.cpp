/*
* Copyright (C) 2010 The Android Open Source Project
*
* Apache License Version 2.0 (�u�{���C�Z���X�v) �Ɋ�Â��ă��C�Z���X����܂��B;
* �{���C�Z���X�ɏ������Ȃ��ꍇ�͂��̃t�@�C�����g�p�ł��܂���B
* �{���C�Z���X�̃R�s�[�́A�ȉ��̏ꏊ�������ł��܂��B
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* �K�p�����@�߂܂��͏��ʂł̓��ӂɂ���Ė������Ȃ�����A�{���C�Z���X�Ɋ�Â��ĔЕz�����\�t�g�E�F�A�́A
* �����َ����킸�A�����Ȃ�ۏ؂��������Ȃ��Ɍ���̂܂�
* �Еz����܂��B
* �{���C�Z���X�ł̌����Ɛ������K�肵���������ẮA
* �{���C�Z���X���Q�Ƃ��Ă��������B
*
*/


#include "ap.Window_Impl_Android.h"
#include "ap.AndroidNativeActivityGlue.h"
#include "ap.Touch_Impl_Android.h"

/**
* ����́Aandroid_native_app_glue ���g�p���Ă���l�C�e�B�u �A�v���P�[�V����
* �̃��C�� �G���g�� �|�C���g�ł��B���ꎩ�̂̃X���b�h�ŃC�x���g ���[�v�ɂ���Ď��s����A
* ���̓C�x���g���󂯎�����葼�̑�������s�����肵�܂��B
*/
void android_main(struct android_app* state) {
	ap::Window_Impl_Android* window = new ap::Window_Impl_Android();
	ap::WindowInitializationParameter* windowparam = new ap::WindowInitializationParameter();
	windowparam->UserData[0] = state;
	window->Initialize(*windowparam);
	ap::Touch_Impl_Android* touch = new ap::Touch_Impl_Android(window);

	while (window->DoEvent()) {
		
		window->Update();

		struct engine* engine = &(window->engine);

		float x=0, y=0;
		touch->GetPosition(x, y);
		glClearColor(x/engine->width, y/engine->height, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		eglSwapBuffers(engine->display, engine->surface);
	}
}
