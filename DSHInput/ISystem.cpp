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
