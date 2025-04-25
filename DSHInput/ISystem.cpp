#include "pch.h"
#include "ISystem.h"
#include "System.h"

const IID DSH::Input::IID_ISystem = __uuidof(ISystem);

HRESULT DSH::Input::CreateSystem::operator()(ISystem** ppSystem) const
{
	if (ppSystem == nullptr) return E_INVALIDARG;
	System* pSystem = new (std::nothrow) System();
	if (pSystem == nullptr) return E_OUTOFMEMORY;
	*ppSystem = pSystem;
	return S_OK;
}

DSH::Input::WindowProcedure::WindowProcedure(ISystem* system) :
	System(system)
{
	if (System != nullptr) System->AddRef();
}

DSH::Input::WindowProcedure::WindowProcedure(const WindowProcedure& other)
{
	System = other.System;
	if (System != nullptr) System->AddRef();
}

DSH::Input::WindowProcedure::WindowProcedure(WindowProcedure&& other) noexcept
{
	System = other.System;
	other.System = nullptr;
}

DSH::Input::WindowProcedure& DSH::Input::WindowProcedure::operator=(const WindowProcedure& other)
{
	if (this != &other)
	{
		if (System != nullptr) System->Release();
		System = other.System;
		if (System != nullptr) System->AddRef();
	}
	return *this;
}

DSH::Input::WindowProcedure& DSH::Input::WindowProcedure::operator=(WindowProcedure&& other) noexcept
{
	if (this != &other)
	{
		if (System != nullptr) System->Release();
		System = other.System;
		other.System = nullptr;
	}
	return *this;
}

DSH::Input::WindowProcedure::~WindowProcedure()
{
	if (System != nullptr) System->Release();
}

LRESULT DSH::Input::WindowProcedure::operator()(HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam) const
{
	if (System == nullptr) return E_NOTIMPL;
	if (System != nullptr &&
		message == WM_INPUT)
	{
		UINT dwSize = 0;
		const HRAWINPUT rawInputHandle = reinterpret_cast<HRAWINPUT>(static_cast<uintptr_t>(lParam));  // NOLINT(performance-no-int-to-ptr)
		constexpr UINT rawInputSize = sizeof(RAWINPUTHEADER);

		if (const UINT result = GetRawInputData(rawInputHandle, RID_INPUT, nullptr, &dwSize, rawInputSize);
			result != 0u) return E_FAIL;

		BYTE* rawInputByteData = new (std::nothrow) BYTE[dwSize];
		if (rawInputByteData == nullptr) return E_OUTOFMEMORY;

		if (const UINT returnedSize = GetRawInputData(rawInputHandle, RID_INPUT, rawInputByteData, &dwSize, rawInputSize); 
			returnedSize != dwSize)
		{
			delete[] rawInputByteData;
			return E_FAIL;
		}

		RAWINPUT* rawInput = reinterpret_cast<RAWINPUT*>(rawInputByteData);

		const LRESULT systemResult = System->Dispatch(wParam & RIM_INPUTSINK, rawInput);

		delete[] rawInputByteData;

		return systemResult;
	}
	return S_OK;
}
