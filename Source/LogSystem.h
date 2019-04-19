#pragma once
#include "Singleton.h"
#include "Logger.h"
#include "FileLogPolicy.h"

class LogSystem
{
public:
	__declspec(dllexport) static void PrintLog(const char* const message);

private:
	static Logger<FileLogPolicy> m_Logger;
};

#define LOG LogSystem::PrintLog
