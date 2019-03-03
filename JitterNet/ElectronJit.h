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

	CorJitResult __stdcall compileMethod(ICorJitInfo*         comp,            /* IN */
		CORINFO_METHOD_INFO* methodInfo,      /* IN */
		unsigned             flags,           /* IN */
		BYTE**               nativeEntry,     /* OUT */
		ULONG*               nativeSizeOfCode /* OUT */
	);

	void clearCache(void);
	BOOL isCacheCleanupRequired(void);

	void ProcessShutdownWork(ICorStaticInfo* statInfo);

	void getVersionIdentifier(GUID* versionIdentifier /* OUT */
	);

	unsigned getMaxIntrinsicSIMDVectorLength(CORJIT_FLAGS cpuCompileFlags);

	void setRealJit(ICorJitCompiler* realJitCompiler);

	ICorJitCompiler* p_jit;
};
