#include "pch.h"
#include "System.h"

#include "Keyboard.h"
//#include "Controller.h"
//#include "Mouse.h"
//#include "MappingContext.h"
//#include "Negative.h"
//#include "SwizzleAxis.h"

DSH::Input::System::System() :
	_referenceCount(1)
{
}


HRESULT DSH::Input::System::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISystem &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::System::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::System::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

LRESULT DSH::Input::System::Dispatch(const bool isFocused, RAWINPUT* rawInput)
{
	LRESULT result = S_OK;
	switch (rawInput->header.dwType)
	{
	case RIM_TYPEMOUSE:
		{
		// TODO: Implement the function to handle mouse input.
		break;
		}
	case RIM_TYPEKEYBOARD:
		{
		const HANDLE deviceHandle = rawInput->header.hDevice;
		if (_keyboards.contains(deviceHandle) == false)
		{
			Device::IKeyboard* pKeyboard = _unhandledKeyboards.top();
			_keyboards[deviceHandle] = pKeyboard;
		}
		result = _keyboards[deviceHandle]->Dispatch(isFocused, rawInput->data.keyboard);
		break;
		}
	default:
		{
		result = S_OK;
		break;
		}
	}
	return result;
}

HRESULT DSH::Input::System::GetKeyboard(Device::IKeyboard** ppKeyboard)
{
	if (const HRESULT registerResult = RegisterRawInputDevices(RAW_INPUT_USAGE_KEYBOARD);
		FAILED(registerResult)) return registerResult;

	if (ppKeyboard == nullptr) return E_INVALIDARG;
	Device::Keyboard* pKeyboard = new (std::nothrow) Device::Keyboard();
	if (pKeyboard == nullptr) return E_OUTOFMEMORY;
	_unhandledKeyboards.push(pKeyboard);
	pKeyboard->AddRef();

	*ppKeyboard = pKeyboard;
	return S_OK;
}

HRESULT DSH::Input::System::CreateMouse(Device::IMouse** ppMouse) const
{
	// TODO: Implement the function to create an instance of the mouse.
	//if (ppMouse == nullptr) return E_INVALIDARG;
	//Device::Mouse* pMouse = new Device::Mouse();
	//if (pMouse == nullptr) return E_OUTOFMEMORY;
	//*ppMouse = pMouse;
	return S_OK;
}

HRESULT DSH::Input::System::CreateController(Device::IController** ppController) const
{
	// TODO: Implement the function to create an instance of the controller.
	//if (ppController == nullptr) return E_INVALIDARG;
	//Device::Controller* pController = new Device::Controller();
	//if (pController == nullptr) return E_OUTOFMEMORY;
	//*ppController = pController;
	return S_OK;
}

HRESULT DSH::Input::System::CreateMappingContext(IMappingContext** ppMappingContext) const
{
	// TODO: Implement the function to create an instance of the mapping context.
	//if (ppMappingContext == nullptr) return E_INVALIDARG;
	//MappingContext* pMappingContext = new MappingContext();
	//if (pMappingContext == nullptr) return E_OUTOFMEMORY;
	//*ppMappingContext = pMappingContext;
	return S_OK;
}

HRESULT DSH::Input::System::CreateModifier(Modifier::INegative** ppModifier) const
{
	// TODO: Implement the function to create an instance of the negative modifier.
	//if (ppModifier == nullptr) return E_INVALIDARG;
	//Modifier::Negative* pModifier = new Modifier::Negative();
	//if (pModifier == nullptr) return E_OUTOFMEMORY;
	//*ppModifier = pModifier;
	return S_OK;
}

HRESULT DSH::Input::System::CreateModifier(Modifier::ISwizzleAxis** ppModifier) const
{
	// TODO: Implement the function to create an instance of the swizzle axis modifier.
	//if (ppModifier == nullptr) return E_INVALIDARG;
	//Modifier::SwizzleAxis* pModifier = new Modifier::SwizzleAxis();
	//if (pModifier == nullptr) return E_OUTOFMEMORY;
	//*ppModifier = pModifier;
	return S_OK;
}

HRESULT DSH::Input::System::RegisterRawInputDevices(const RawInputUsageType usUsage)
{
	_rawInputDevices.push_back(
		RAWINPUTDEVICE
		{
			.usUsagePage= 0x01,
			.usUsage = usUsage,
			.dwFlags= RIDEV_DEVNOTIFY,
			.hwndTarget= NULL
		});
	if (const bool result = ::RegisterRawInputDevices(_rawInputDevices.data(),
	                                                  static_cast<UINT>(_rawInputDevices.size()),
	                                                  sizeof(RAWINPUTDEVICE));
		result == false)
	{
		const DWORD error = ::GetLastError();
		return HRESULT_FROM_WIN32(error);
	}
	return S_OK;
}