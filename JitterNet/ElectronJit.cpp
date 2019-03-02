#include "stdafx.h"
#include "ElectronJit.h"
#include "debugUtils.h"

static BYTE returns11[] = { 0xB8, 0x0A, 0x00, 0x00, 0x00, 0xC3 }; // MOV EAX, 10 then RET

ElectronJit::ElectronJit()
{
	LOG_C;

	if (!g_getJitEx)
	{
		g_getJitEx = (getJitEx)GetProcAddress(LoadLibraryW(L"r_clrjit.dll"), "getJit");
		g_jitStartupEx = (jitStartupEx)GetProcAddress(LoadLibraryW(L"r_clrjit.dll"), "jitStartup");
	}

	p_jit = nullptr;
}

CorJitResult ElectronJit::compileMethod(ICorJitInfo* comp, CORINFO_METHOD_INFO* info, unsigned flags,
	BYTE** nativeEntry, ULONG* nativeSizeOfCode)
{
	LOG_C;

	const auto name = comp->getMethodNameFromMetadata(info->ftn, nullptr, nullptr, nullptr);

	if (strcmp(name, "Main") == 0)
	{
		void *codeBlock, *dummyCold, *dummyRoData;

		comp->allocMem(sizeof(BYTE) * 6, 0, 0, 0, CORJIT_ALLOCMEM_DEFAULT_CODE_ALIGN, &codeBlock, &dummyCold, &dummyRoData);

		memcpy(codeBlock, returns11, sizeof(BYTE) * 6);
		*nativeEntry = (BYTE*)codeBlock;
		return CORJIT_OK;
	}

	return p_jit->compileMethod(comp, info, flags, nativeEntry, nativeSizeOfCode);
}

void ElectronJit::clearCache()
{
	p_jit->clearCache();
	// TODO?
}

BOOL ElectronJit::isCacheCleanupRequired()
{
	LOG_C;
	return p_jit->isCacheCleanupRequired();
}

void ElectronJit::getVersionIdentifier(GUID* versionIdentifier)
{
	LOG_C;
	p_jit->getVersionIdentifier(versionIdentifier);
}
