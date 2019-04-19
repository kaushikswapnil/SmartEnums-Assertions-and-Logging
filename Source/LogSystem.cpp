#include "LogSystem.h"

Logger<FileLogPolicy> LogSystem::m_Logger("essentials_log.txt");

void LogSystem::PrintLog(const char* const message)
{
	m_Logger.PrintLog(message);
}
