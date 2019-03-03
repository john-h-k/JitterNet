#include "stdafx.h"
#include "ElectronJit.h"
#include "debugUtils.h"
#include <cassert>

static BYTE returns11[] = { 0xB8, 0x0A, 0x00, 0x00, 0x00, 0xC3 }; // MOV EAX, 10 then RET

const GUID version =
{ /* d609bed1-7831-49fc-bd49-b6f054dd4d46 */
	0xd609bed1,
	0x7831,
	0x49fc,
	{ 0xbd, 0x49, 0xb6, 0xf0, 0x54, 0xdd, 0x4d, 0x46 }
};

getJitEx g_getJitEx;
jitStartupEx g_jitStartupEx;

ElectronJit::ElectronJit()
{
	p_jit = nullptr;
}

CorJitResult ElectronJit::compileMethod(ICorJitInfo* comp, CORINFO_METHOD_INFO* info, unsigned flags,
	BYTE** nativeEntry, ULONG* nativeSizeOfCode)
{
	LOG_C;

	const auto name = comp->getMethodNameFromMetadata(info->ftn, nullptr, nullptr, nullptr);

	if (strcmp(name, "Main") == 0) // this is wrong, I know
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
	assert(versionIdentifier);
	memcpy(versionIdentifier, &version, sizeof(GUID));
}

unsigned ElectronJit::getMaxIntrinsicSIMDVectorLength(CORJIT_FLAGS cpuCompileFlags)
{
	return p_jit->getMaxIntrinsicSIMDVectorLength(cpuCompileFlags);
}

void ElectronJit::setRealJit(ICorJitCompiler* realJitCompiler)
{
	p_jit->setRealJit(realJitCompiler);
}

void ElectronJit::ProcessShutdownWork(ICorStaticInfo* info)
{
	p_jit->ProcessShutdownWork(info);
}

//unsigned ElectronJit::getMaxIntrinsicSIMDVectorLength(CORJIT_FLAGS cpuCompileFlags)
//{
//	return p_jit->getMaxIntrinsicSIMDVectorLength(cpuCompileFlags);
//}
//
//void ElectronJit::setRealJit(ICorJitCompiler* realJitCompiler)
//{
//	p_jit->setRealJit(realJitCompiler);
//}
