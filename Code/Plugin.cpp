#include "StdAfx.h"
#include "Plugin.h"
#include "IPublicInterface.h"

#pragma comment(lib, "ThirdPartyLib.lib")

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>

IEntityRegistrator *IEntityRegistrator::g_pFirst = nullptr;
IEntityRegistrator *IEntityRegistrator::g_pLast = nullptr;

CPlugin::~CPlugin()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);

	IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
	while (pTemp != nullptr)
	{
		pTemp->Unregister();
		pTemp = pTemp->m_pNext;
	}
}

bool CPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	// Third part lib test
	CreatePublicInterface();
	IPublicInterface * pIntf = GetPublicInterface();
	string name = pIntf->GetName();
	string version = pIntf->GetVersion();
	DestroyPublicInterface();
	// ~Third part lib test

	CryLogAlways("Loaded ThirdPartyLib. Name: %s, Version: %s", name, version);

	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this);

	return true;
}

void CPlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_GAME_POST_INIT:
	{
		// Register entities
		IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
		while (pTemp != nullptr)
		{
			pTemp->Register();
			pTemp = pTemp->m_pNext;
		}
	}
	break;
	}
}

CRYREGISTER_SINGLETON_CLASS(CPlugin)