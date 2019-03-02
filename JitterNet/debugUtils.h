#pragma once
#include <fstream>

static std::fstream file("log.txt", std::ios::out | std::ios::trunc);

static void LogEnteredFuncDebug(const char* name)
{
#ifdef _DEBUG
	file << "Entered " << name << std::endl;
	file.flush();
#endif
}

#define LOG_C LogEnteredFuncDebug(__func__)