#pragma once
#include "IKeyboard.h"

namespace DSH::Input
{
	namespace Component
	{
		class ButtonComponent;
	}

	namespace Device
	{
		class Keyboard final : public IKeyboard
		{
		public:
			Keyboard();
			~Keyboard() override;
			
			HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
			ULONG AddRef() override;
			ULONG Release() override;

			LRESULT Dispatch(bool isFocused, const RAWKEYBOARD& rawKeyboard) override;

			HRESULT GetComponent(Key key, Component::IButtonComponent** ppComponent) override;

		private:
			ULONG _referenceCount;

			std::unordered_map<Key, Component::ButtonComponent*> _keys;
		};
	}
}
