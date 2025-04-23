#include "pch.h"
#include "ISystem.h"

const IID DSH::Input::IID_ISystem = __uuidof(ISystem);

HRESULT DSH::Input::CreateSystem::operator()(ISystem** ppSystem) const
{
	// TODO: Implement the function to create an instance of the system.
	//if (ppSystem == nullptr) return E_INVALIDARG;
	//System* pSystem = new System();
	//if (pSystem == nullptr) return E_OUTOFMEMORY;
	//*ppSystem = pSystem;
	//return S_OK;
}
