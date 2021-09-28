
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <array>

#ifdef __ANDROID__
#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <android/log.h>

#else

// GLFW
#if _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#else
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <X11/extensions/Xrandr.h>
#endif

#include <GLFW/glfw3.h>

#if _WIN32
#include <GLFW/glfw3native.h>
#endif

#endif

namespace ap
{
	class Window;
	class Keyboard;

	enum class ErrorCode : int32_t
	{
		OK,
		FailedInitializeWindowSystem,
		FailedCreateWindow,
		Unknown,
	};


	enum class InputState : int32_t
	{
		Push,
		Release,
		Hold,
		Free,
	};

	/**
	@brief �}�E�X�̃{�^���ꗗ�������񋓌^
	*/
	enum class MouseButtons : int32_t
	{
		/**
		@brief ���{�^��
		*/
		ButtonLeft = 0,

		/**
		@brief �E�{�^��
		*/
		ButtonRight = 1,

		/**
		@brief �����{�^��
		*/
		ButtonMiddle = 2,

		/**
		@brief �T�u�{�^��1
		*/
		SubButton1 = 3,

		/**
		@brief �T�u�{�^��2
		*/
		SubButton2 = 4,

		/**
		@brief �T�u�{�^��3
		*/
		SubButton3 = 5,

		/**
		@brief �T�u�{�^��4
		*/
		SubButton4 = 6,

		/**
		@brief �T�u�{�^��5
		*/
		SubButton5 = 7,
	};

	enum class Keys : int32_t
	{
		Unknown,
		Space,			///< �X�y�[�X
		Apostrophe,		///< �F (US�z��ł� ` )
		Comma,			///< �C
		Minus,			///< �|
		Period,			///< �D
		Slash,			///< �^
		Num0,			///< 0
		Num1,			///< 1
		Num2,			///< 2
		Num3,			///< 3
		Num4,			///< 4
		Num5,			///< 5
		Num6,			///< 6
		Num7,			///< 7
		Num8,			///< 8
		Num9,			///< 9
		Semicolon,		///< �G
		Equal,			///< �O (US�z��ł� �� )
		A,				///< A
		B,				///< B
		C,				///< C
		D,				///< D
		E,			///< E
		F,				///< F
		G,				///< G
		H,				///< H
		I,				///< I
		J,				///< J
		K,				///< K
		L,				///< L
		M,				///< M
		N,				///< N
		O,				///< O
		P,				///< P
		Q,				///< Q
		R,				///< R
		S,				///< S
		T,				///< T
		U,				///< U
		V,				///< V
		W,				///< W
		X,				///< X
		Y,				///< Y
		Z,				///< Z
		LeftBracket,	///< @ (US�z��ł� �m )
		Backslash,		///< ] (US�z��ł� �_ )
		RightBracket,	///< [ (US�z��ł� �n )
		GraveAccent,	///< ���p/�S�p
		World1,
		World2,
		Escape,			///< Esc
		Enter,			///< Enter
		Tab,			///< Tab 
		Backspace,		///< BackSpace
		Insert,			///< Insert 
		Delete,			///< Delete 
		Right,			///< ��
		Left,			///< ��
		Down,			///< ��
		Up,				///< ��
		PageUp,			///< PageUp
		PageDown,		///< PageDown
		Home,			///< Home 
		End,			///< End
		CapsLock,		///< CapsLock
		ScrollLock,		///< ScrollLock
		NumLock,		///< NumLock
		PrintScreen,	///< PrintScreen
		Pause,			///< Pause
		F1,				///< F1
		F2,				///< F2
		F3,				///< F3
		F4,				///< F4
		F5,				///< F5
		F6,				///< F6
		F7,				///< F7
		F8,				///< F8
		F9,				///< F9
		F10,			///< F10
		F11,			///< F11
		F12,			///< F12
		F13,			///< F13
		F14,			///< F14
		F15,			///< F15
		F16,			///< F16
		F17,			///< F17
		F18,			///< F18
		F19,			///< F19
		F20,			///< F20
		F21,			///< F21
		F22,			///< F22
		F23,			///< F23
		F24,			///< F24
		F25,			///< F25
		Keypad0,		///< �e���L�[��0
		Keypad1,		///< �e���L�[��1
		Keypad2,		///< �e���L�[��2
		Keypad3,		///< �e���L�[��3
		Keypad4,		///< �e���L�[��4
		Keypad5,		///< �e���L�[��5
		Keypad6,		///< �e���L�[��6
		Keypad7,		///< �e���L�[��7
		Keypad8,		///< �e���L�[��8
		Keypad9,		///< �e���L�[��9
		KeypadDecimal,	///< �e���L�[�́D
		KeypadDivide,	///< �e���L�[�́^
		KeypadMultiply,	///< �e���L�[�́�
		KeypadSubstract,///< �e���L�[�́|
		KeypadAdd,		///< �e���L�[�́{
		KeypadEnter,	///< �e���L�[��Enter
		KeypadEqual,	///< �e���L�[�́�
		LeftShift,		///< ��Shift
		LeftControl,	///< ��Ctrl
		LeftAlt,		///< ��Alt
		LeftWin,		///< ��Win
		RightShift,		///< �EShift
		RightControl,	///< �ECtrl
		RightAlt,		///< �EAlt
		RightWin,		///< �EWin
		Menu,			///< �R���e�L�X�g���j���[
		Last,
		MAX
	};

	struct WindowInitializationParameter
	{
		std::u16string	Title;
		int32_t	WindowWidth = 0;
		int32_t WindowHeight = 0;
		bool	IsFullscreenMode = false;


		//GraphicsDeviceType	GraphicsDevice = GraphicsDeviceType::Default;
		//WindowPositionType	WindowPosition = WindowPositionType::Centering;
		//ColorSpaceType		ColorSpace = ColorSpaceType::GammaSpace;

		std::array<void*, 3> UserData;
	};
}