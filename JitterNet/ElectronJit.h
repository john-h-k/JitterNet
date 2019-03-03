#pragma once
#include "corjit.h"

extern "C" typedef ICorJitCompiler* (__stdcall *getJitEx)();
extern "C" typedef void (__stdcall *jitStartupEx)(ICorJitHost*);

extern getJitEx g_getJitEx;
extern jitStartupEx g_jitStartupEx;

class ElectronJit : public ICorJitCompiler  // NOLINT(hicpp-special-member-functions)
{
public:
	virtual ~ElectronJit() = default;

	CorJitResult __stdcall compileMethod(ICorJitInfo* comp, CORINFO_METHOD_INFO* info, unsigned flags,
		BYTE** nativeEntry, ULONG* nativeSizeOfCode);
	void clearCache();
	BOOL isCacheCleanupRequired();
	void getVersionIdentifier(GUID* versionIdentifier);

	void ProcessShutdownWork(ICorStaticInfo* info) override;
	unsigned getMaxIntrinsicSIMDVectorLength(CORJIT_FLAGS cpuCompileFlags);
	void setRealJit(ICorJitCompiler* realJitCompiler);
	ICorJitCompiler* p_jit;	
};
