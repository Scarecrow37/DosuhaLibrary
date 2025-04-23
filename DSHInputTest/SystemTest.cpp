#include "pch.h"
#include "CppUnitTest.h"
#include "DSHInput/ISystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSH::Input
{
	TEST_CLASS(System)
	{
	public:

		TEST_METHOD(SystemCreationSuccess)
		{
			CreateSystem createSystem;
			ISystem* pSystem = nullptr;
			HRESULT hr = createSystem(&pSystem);
			Assert::IsTrue(SUCCEEDED(hr));
			Assert::IsNotNull(pSystem);
			pSystem->Release();
		}

		TEST_METHOD(SystemCreationFailure)
		{
			CreateSystem createSystem;
			ISystem* pSystem = nullptr;
			HRESULT hr = createSystem(nullptr);
			Assert::IsTrue(FAILED(hr));
			Assert::IsNull(pSystem);
		}
	};
}
