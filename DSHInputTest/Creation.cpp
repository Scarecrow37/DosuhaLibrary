#include "pch.h"
#include "CppUnitTest.h"
#include "DSHInput/ISystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSH::Input::System
{
	TEST_CLASS(Creation)
	{
	public:

		TEST_METHOD(Success)
		{
			constexpr CreateSystem createSystem;
			ISystem* pSystem = nullptr;
			const HRESULT hr = createSystem(&pSystem);
			Assert::IsTrue(SUCCEEDED(hr));
			Assert::IsNotNull(pSystem);
			pSystem->Release();
		}

		TEST_METHOD(Failure)
		{
			constexpr CreateSystem createSystem;
			const HRESULT hr = createSystem(nullptr);
			Assert::IsTrue(FAILED(hr));
		}
	};
}
