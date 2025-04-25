#pragma once

namespace DSH::Input
{
	struct ISystem;

	/**
	 * @brief CreateSystem is a function object that creates an instance of the system.
	 * @note This is a function object, not a function pointer.
	 */
	EXTERN_C struct DSH_INPUT_API CreateSystem
	{
		/**
		 * @brief Creates an instance of the system.
		 * @param ppSystem Pointer to a pointer to the system instance.
		 * @return E_INVALIDARG: if ppSystem is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the system instance is created successfully.
		 */
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};

	EXTERN_C struct DSH_INPUT_API WindowProcedure
	{
		explicit WindowProcedure(ISystem* system);
		WindowProcedure(const WindowProcedure& other);
		WindowProcedure(WindowProcedure&& other) noexcept;
		WindowProcedure& operator=(const WindowProcedure& other);
		WindowProcedure& operator=(WindowProcedure&& other) noexcept;
		~WindowProcedure();

		/**
		 * @brief Calls the system's dispatch function.
		 * @param windowHandle The handle to the window.
		 * @param message The message to be dispatched.
		 * @param wParam The wParam of the message.
		 * @param lParam The lParam of the message.
		 * @return S_OK: if the message is dispatched successfully.
		 * @return E_NOTIMPL: if the system is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return E_FAIL: GetRawInputData failed.
		 */
		LRESULT CALLBACK operator()(
			/* [annotation][in] */
			_In_ HWND windowHandle,
			/* [annotation][in] */
			_In_ UINT message,
			/* [annotation][in] */
			_In_ WPARAM wParam,
			/* [annotation][in] */
			_In_ LPARAM lParam) const;

		ISystem* System;
	};
}

namespace DSH::Input
{
	struct IMappingContext;

	namespace Device
	{
		struct IKeyboard;
		struct IMouse;
		struct IController;
	}

	namespace Modifier
	{
		struct INegative;
		struct ISwizzleAxis;
	}

	/**
	 * @brief IID_ISystem is the interface ID for the system interface.
	 * @note This is used to identify the system interface.
	 */
	EXTERN_C const IID IID_ISystem;

	/**
	 * @brief ISystem is the interface for the system.
	 * @note This interface is used to create instances of the input devices and modifiers.
	 */
	EXTERN_C MIDL_INTERFACE("e6352f7a-9bf1-4896-8ad0-9335fe5aa1b7")
		DSH_INPUT_API ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual LRESULT CALLBACK Dispatch(bool isFocused, RAWINPUT* rawInput) = 0;

		/**
		 * @brief Gets the keyboard instance.
		 * @param ppKeyboard Pointer to a pointer to the keyboard instance.
		 * @return E_INVALIDARG: if ppKeyboard is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the keyboard instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE GetKeyboard(
			/* [annotation][out] */
			_Out_ Device::IKeyboard** ppKeyboard) = 0;

		/**
		 * @brief Creates an instance of the mouse.
		 * @param ppMouse Pointer to a pointer to the mouse instance.
		 * @return E_INVALIDARG: if ppMouse is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the mouse instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE CreateMouse(
			/* [annotation][out] */
			_Out_ Device::IMouse** ppMouse) const = 0;

		/**
		 * @brief Creates an instance of the controller.
		 * @param ppController Pointer to a pointer to the controller instance.
		 * @return E_INVALIDARG: if ppController is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the controller instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE CreateController(
			/* [annotation][out] */
			_Out_ Device::IController** ppController) const = 0;

		/**
		 * @brief Creates an instance of the mapping context.
		 * @param ppMappingContext Pointer to a pointer to the mapping context instance.
		 * @return E_INVALIDARG: if ppMappingContext is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the mapping context instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE CreateMappingContext(
			/* [annotation][out] */
			_Out_ IMappingContext** ppMappingContext) const = 0;

		/**
		 * @brief Creates an instance of the negative modifier.
		 * @param ppModifier Pointer to a pointer to the negative modifier instance.
		 * @return E_INVALIDARG: if ppModifier is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the negative modifier instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE CreateModifier(
			/* [annotation][out] */
			_Out_ Modifier::INegative** ppModifier) const = 0;

		/**
		 * @brief Creates an instance of the swizzle axis modifier.
		 * @param ppModifier Pointer to a pointer to the swizzle axis modifier instance.
		 * @return E_INVALIDARG: if ppModifier is null.
		 * @return E_OUTOFMEMORY: if memory allocation fails.
		 * @return S_OK: if the swizzle axis modifier instance is created successfully.
		 */
		virtual HRESULT STDMETHODCALLTYPE CreateModifier(
			/* [annotation][out] */
			_Out_ Modifier::ISwizzleAxis** ppModifier) const = 0;
	};
}