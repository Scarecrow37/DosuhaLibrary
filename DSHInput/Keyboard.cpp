#include "pch.h"
#include "Keyboard.h"

DSH::Input::Device::Keyboard::Keyboard() :
	_referenceCount(1)
{
}

DSH::Input::Device::Keyboard::~Keyboard()
{
	// TODO: Implement a better way to release the keys
	//std::ranges::for_each(_keys | std::views::values, [](Component::ButtonComponent* key) { key->Release(); });
	//_keys.clear();
}

HRESULT DSH::Input::Device::Keyboard::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IKeyboard &&
		riid != IID_IDevice &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Device::Keyboard::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Device::Keyboard::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

LRESULT DSH::Input::Device::Keyboard::Dispatch(bool isFocused, const RAWKEYBOARD& rawKeyboard)
{
    WORD scanCode = 0;
    BOOL keyUp = rawKeyboard.Flags & RI_KEY_BREAK;

    // Ignore key overrun state and keys not mapped to any virtual key code
    if (rawKeyboard.MakeCode == KEYBOARD_OVERRUN_MAKE_CODE || rawKeyboard.VKey >= UCHAR_MAX) return E_FAIL;

    if (rawKeyboard.MakeCode)
    {
        // Compose the full scan code value with its extended byte
        scanCode = MAKEWORD(rawKeyboard.MakeCode & 0x7f, ((rawKeyboard.Flags & RI_KEY_E0) ? 0xe0 : ((rawKeyboard.Flags & RI_KEY_E1) ? 0xe1 : 0x00)));
    }
    else
    {
        // Scan code value may be empty for some buttons (for example multimedia buttons)
        // Try to get the scan code from the virtual key code
        scanCode = LOWORD(MapVirtualKey(rawKeyboard.VKey, MAPVK_VK_TO_VSC_EX));
    }

	if (_keys.contains(static_cast<Key>(scanCode)))
	{
		// TODO: Implement a better way to get the state of the keys
		Component::ButtonComponent* pButtonComponent = _keys[scanCode];
		//pButtonComponent->SetState(keyUp ? Component::ButtonState::Released : Component::ButtonState::Pressed);
	}

	return S_OK;
}

HRESULT DSH::Input::Device::Keyboard::GetComponent(const Key key, Component::IButtonComponent** ppComponent)
{
	// TODO: Implement a better way to get the state of the keys
	//if (key == Key::Max) return E_INVALIDARG;
	//if (ppComponent == nullptr) return E_INVALIDARG;
	//Component::ButtonComponent* pButtonComponent = nullptr;
	//if (_keys.contains(key) == false)
	//{
	//	pButtonComponent = new Component::ButtonComponent();
	//	if (pButtonComponent == nullptr) return E_OUTOFMEMORY;
	//	_keys[key] = pButtonComponent;
	//}
	//else pButtonComponent = _keys[key];
	//pButtonComponent->AddRef();
	//*ppComponent = pButtonComponent;
	return S_OK;
}
