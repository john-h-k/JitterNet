#pragma once
#include "corjit.h"

extern "C" typedef ICorJitCompiler* (__stdcall *getJitEx)();
extern "C" typedef void (__stdcall *jitStartupEx)(ICorJitHost*);

extern getJitEx g_getJitEx;
extern jitStartupEx g_jitStartupEx;

class ElectronJit : public ICorJitCompiler  // NOLINT(hicpp-special-member-functions)
{
public:
	ElectronJit();
	virtual ~ElectronJit() = default;

	CorJitResult __stdcall compileMethod(ICorJitInfo* comp, CORINFO_METHOD_INFO* info, unsigned flags,
		BYTE** nativeEntry, ULONG* nativeSizeOfCode) override;
	void clearCache() override;
	BOOL isCacheCleanupRequired() override;
	void getVersionIdentifier(GUID* versionIdentifier) override;

	ICorJitCompiler* p_jit;	
};
