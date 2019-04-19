#pragma once
#include "CriticalSection.h"
#include <sstream>
#include "FileLogPolicy.h"

template<class LoggingPolicy>
class Logger 
{
public:
	Logger(const std::string& ostreamName)
	{
		m_Policy.OpenOStream(ostreamName);
	}

	~Logger()
	{
		m_Policy.CloseOStream();
	}

	template<typename...Args>
	void PrintLog(Args... args)
	{
		m_Lock.Lock();
		PrintLog_Internal(args...);
		m_Lock.Unlock();
	}
private:
	void PrintLog_Internal()
	{
		m_Policy.Write(m_LogStream.str());
		m_LogStream.clear();
	}

	template<typename FirstParam, typename...Args>
	void PrintLog_Internal(FirstParam firstParam, Args... args)
	{
		m_LogStream << firstParam;
		PrintLog_Internal(args...);
	}

	LoggingPolicy m_Policy;
	CriticalSection m_Lock;
	std::stringstream m_LogStream;
};
