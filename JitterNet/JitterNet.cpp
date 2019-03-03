// JitterNet.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ElectronJit.h"
#include <cstdint>
#include <fstream>
#include "debugUtils.h"

struct CoreClrCallbacks;

static ElectronJit* jit;

extern "C" __declspec(dllexport) ICorJitCompiler* __stdcall getJit()
{
	LOG_C;

	jit = new ElectronJit();
	jit->p_jit = g_getJitEx();
	return jit;
}

extern "C" __declspec(dllexport) void __stdcall sxsJitStartup(CoreClrCallbacks const& cccallbacks)
{
	LOG_C;
	// NOP, TODO
}

extern "C" __declspec(dllexport) void __stdcall jitStartup(ICorJitHost* jitHost)
{
	LOG_C;

	if (!g_getJitEx)
	{
		g_getJitEx = (getJitEx)GetProcAddress(LoadLibraryW(L"r_clrjit.dll"), "getJit");
		g_jitStartupEx = (jitStartupEx)GetProcAddress(LoadLibraryW(L"r_clrjit.dll"), "jitStartup");
	}

	g_jitStartupEx(jitHost);
	// TODO - currently nothing to do
}