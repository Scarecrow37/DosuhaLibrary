#include "pch.h"
#include "CppUnitTest.h"
#include "DSHInput/ISystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSH::Input::System
{
	TEST_CLASS(Dispath)
	{
	public:

		TEST_METHOD(FailedWithInvalidHandle)
		{
			constexpr CreateSystem createSystem;
			ISystem* pSystem = nullptr;
			const HRESULT hr = createSystem(&pSystem);
			Assert::IsTrue(SUCCEEDED(hr));
			Assert::IsNotNull(pSystem);

			RAWINPUT rawInput
			{
				.header = RAWINPUTHEADER
				{
					.dwType = RIM_TYPEKEYBOARD,
					.dwSize = sizeof(RAWINPUT),
					.hDevice = INVALID_HANDLE_VALUE,
					.wParam = 0
				},
				.data =
				{
					.keyboard = RAWKEYBOARD
					{
						.MakeCode = 0x001E,
						.Flags = RI_KEY_MAKE,
						.Reserved = 0,
						.VKey = 0x41, // 'A' key
						.Message = WM_KEYDOWN,
						.ExtraInformation = NULL
					}
				}
			};

			const LRESULT result = pSystem->Dispatch(true, &rawInput);
			Assert::IsTrue(FAILED(result));
			pSystem->Release();
		}
	};
}
