#pragma once
#include "ISystem.h"

namespace DSH::Input
{
	namespace Device
	{
		struct IRawDevice;
	}

	class System final : public ISystem
	{
	public:
		System();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		LRESULT Dispatch(bool isFocused, RAWINPUT* rawInput) override;

		HRESULT GetKeyboard(Device::IKeyboard** ppKeyboard) override;
		HRESULT CreateMouse(Device::IMouse** ppMouse) const override;
		HRESULT CreateController(Device::IController** ppController) const override;
		HRESULT CreateMappingContext(IMappingContext** ppMappingContext) const override;
		HRESULT CreateModifier(Modifier::INegative** ppModifier) const override;
		HRESULT CreateModifier(Modifier::ISwizzleAxis** ppModifier) const override;

	private:
		enum RawInputUsageType : uint8_t
		{
			RAW_INPUT_USAGE_MOUSE = 0x02,
			RAW_INPUT_USAGE_KEYBOARD = 0x06,
		};

		HRESULT RegisterRawInputDevices(RawInputUsageType usUsage);

		ULONG _referenceCount;

		std::vector<RAWINPUTDEVICE> _rawInputDevices;

		std::stack<Device::IKeyboard*> _unhandledKeyboards;
		std::unordered_map<HANDLE, Device::IKeyboard*> _keyboards;

		std::stack<Device::IMouse*> _unhandledMice;
		std::unordered_map<HANDLE, Device::IMouse*> _mice;
	};
}
