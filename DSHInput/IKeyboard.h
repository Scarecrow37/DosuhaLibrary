#pragma once
#include "IDevice.h"

namespace DSH::Input
{
	namespace Component
	{
		struct IButtonComponent;
	}

	namespace Device
	{
		EXTERN_C const IID IID_IKeyboard;

		EXTERN_C MIDL_INTERFACE("b8bb3047-77c7-4082-a4f1-82c2e8b61b92")
			DSH_INPUT_API IKeyboard : IDevice
		{
			enum Key : WORD
			{
				SYSTEM_POWER_DOWN = 0x0081,
				SYSTEM_SLEEP = 0x0082,
				SYSTEM_WAKEUP = 0x0083,
				KEYBOARD_A = 0x001E,
				KEYBOARD_B = 0x0030,
				KEYBOARD_C = 0x002E,
				KEYBOARD_D = 0x0020,
				KEYBOARD_E = 0x0012,
				KEYBOARD_F = 0x0021,
				KEYBOARD_G = 0x0022,
				KEYBOARD_H = 0x0023,
				KEYBOARD_I = 0x0017,
				KEYBOARD_J = 0x0024,
				KEYBOARD_K = 0x0025,
				KEYBOARD_L = 0x0026,
				KEYBOARD_M = 0x0032,
				KEYBOARD_N = 0x0031,
				KEYBOARD_O = 0x0018,
				KEYBOARD_P = 0x0019,
				KEYBOARD_Q = 0x0010,
				KEYBOARD_R = 0x0013,
				KEYBOARD_S = 0x001F,
				KEYBOARD_T = 0x0014,
				KEYBOARD_U = 0x0016,
				KEYBOARD_V = 0x002F,
				KEYBOARD_W = 0x0011,
				KEYBOARD_X = 0x002D,
				KEYBOARD_Y = 0x0015,
				KEYBOARD_Z = 0x002C,
				KEYBOARD_1 = 0x0002,
				KEYBOARD_2 = 0x0003,
				KEYBOARD_3 = 0x0004,
				KEYBOARD_4 = 0x0005,
				KEYBOARD_5 = 0x0006,
				KEYBOARD_6 = 0x0007,
				KEYBOARD_7 = 0x0008,
				KEYBOARD_8 = 0x0009,
				KEYBOARD_9 = 0x000A,
				KEYBOARD_0 = 0x000B,
				KEYBOARD_RETURN = 0x001C,
				KEYBOARD_ESCAPE = 0x0001,
				KEYBOARD_DELETE = 0x000E,
				KEYBOARD_TAB = 0x000F,
				KEYBOARD_SPACE_BAR = 0x0039,
				KEYBOARD_MINUS = 0x000C,
				KEYBOARD_EQUAL = 0x000D,
				KEYBOARD_LEFT_BRACKET = 0x001A,
				KEYBOARD_RIGHT_BRACKET = 0x001B,
				KEYBOARD_PIPE = 0x002B,
				KEYBOARD_SEMICOLON = 0x0027,
				KEYBOARD_APOSTROPHE = 0x0028,
				KEYBOARD_GRAVE_ACCENT = 0x0029,
				KEYBOARD_COMMA = 0x0033,
				KEYBOARD_PERIOD = 0x0034,
				KEYBOARD_SLASH = 0x0035,
				KEYBOARD_CAPS_LOCK = 0x003A,
				KEYBOARD_F1 = 0x003B,
				KEYBOARD_F2 = 0x003C,
				KEYBOARD_F3 = 0x003D,
				KEYBOARD_F4 = 0x003E,
				KEYBOARD_F5 = 0x003F,
				KEYBOARD_F6 = 0x0040,
				KEYBOARD_F7 = 0x0041,
				KEYBOARD_F8 = 0x0042,
				KEYBOARD_F9 = 0x0043,
				KEYBOARD_F10 = 0x0044,
				KEYBOARD_F11 = 0x0057,
				KEYBOARD_F12 = 0x0058,
				KEYBOARD_SCREEN_CAPTURE = 0xE037,
				KEYBOARD_SCROLL_LOCK = 0x0046,
				KEYBOARD_PAUSE = 0xE145,
				KEYBOARD_INSERT = 0xE052,
				KEYBOARD_HOME = 0xE047,
				KEYBOARD_PAGE_UP = 0xE049,
				KEYBOARD_DELETE_FORWARD = 0xE053,
				KEYBOARD_END = 0xE04F,
				KEYBOARD_PAGE_DOWN = 0xE051,
				KEYBOARD_RIGHT_ARROW = 0xE04D,
				KEYBOARD_LEFT_ARROW = 0xE04B,
				KEYBOARD_DOWN_ARROW = 0xE050,
				KEYBOARD_UP_ARROW = 0xE048,
				KEYPAD_NUM_LOCK_CLEAR = 0x0045,
				KEYPAD_SLASH = 0xE035,
				KEYPAD_ASTERISK = 0x0037,
				KEYPAD_PLUS = 0x004E,
				KEYPAD_ENTER = 0xE01C,
				KEYPAD_1 = 0x004F,
				KEYPAD_2 = 0x0050,
				KEYPAD_3 = 0x0051,
				KEYPAD_4 = 0x004B,
				KEYPAD_5 = 0x004C,
				KEYPAD_6 = 0x004D,
				KEYPAD_7 = 0x0047,
				KEYPAD_8 = 0x0048,
				KEYPAD_9 = 0x0049,
				KEYPAD_0 = 0x0052,
				KEYPAD_PERIOD = 0x0053,
				KEYBOARD_LEFT_CONTROL = 0x001D,
				KEYBOARD_LEFT_SHIFT = 0x002A,
				KEYBOARD_LEFT_ALT = 0x0038,
				KEYBOARD_LEFT_GUI = 0xE05B,
				KEYBOARD_RIGHT_CONTROL = 0xE01D,
				KEYBOARD_RIGHT_SHIFT = 0x0036,
				KEYBOARD_RIGHT_ALT = 0xE038,
				KEYBOARD_RIGHT_GUI = 0xE05C,
			};

		/**
		 * @brief Dispatches the raw input data to the appropriate device.
		 * @param isFocused Indicates whether the window is focused.
		 * @param rawKeyboard Pointer to the raw keyboard input data.
		 * @return S_OK: if the message is dispatched successfully.
		 */
		virtual LRESULT STDMETHODCALLTYPE Dispatch(
			/* [annotation][in] */
			_In_ bool isFocused,
			/* [annotation][in] */
			_In_ const RAWKEYBOARD& rawKeyboard) = 0;

		/**
		 * @brief Gets the component of the specified key.
		 * @param key The key to get the component for.
		 * @param ppComponent Pointer to a pointer to the button component.
		 * @return E_INVALIDARG: if ppComponent is null or key is invalid.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the component is retrieved successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE GetComponent(
			/* [annotation][in] */
			_In_ Key key,
			/* [annotation][out] */
			_Out_ Component::IButtonComponent** ppComponent) = 0;
		};
	}
}
