#pragma once

#ifdef _DEBUG
	#include "windows.h"
	#include <string>
	#include <stdexcept>

	#include "smartenum.h"
	#include "LogSystem.h"

//#####################
//Errors - Documentation
//#####################
//Assert Levels (More information is given near the macros themselves.):
//---------------------
//Provides 4 levels of asserts, Warning, SoftAssert, HardAssert, & CriticalRunTimeError
//	WARNING = Print warning to log
//	SOFTASSERT = Break into debugger if possible, log the assert. Can be continued
//	HARDASSERT = Break into debugger if possible, log the assert. Calls abort() after logging
//	CRITICAL_RUNTIME_ERROR = throws a std::runtime_error with the message provided;
//---------------------
//

	namespace Essentials
	{
		namespace Error
		{
			SMARTENUM(AssertLevel, Warning, SoftAssert, HardAssert, CriticalRunTimeError);

			inline void ReportAssertion(const AssertLevel& assertLevel, const char* const message, const char* const conditionStr, const char* const fileName, const long lineNumber)
			{
				//#TODO Add better reporting capabilities
				std::string output = "[" + assertLevel.ToString() + "] ";
				output.append(message);
				output.append(". Condition Failed: ");
				output.append(conditionStr);
				output.append(". File: ");
				output.append(fileName);
				output.append(". Line: ");
				output.append(std::to_string(lineNumber));
				std::cout << output;

				//LOG(output.c_str());
			}
		}
	}

	//Warning will print a warning message to the log if the condition is false
	#define WARNING(condition, message) \
	do \
	{ \
		if (!(condition)) \
		{ \
			Essentials::Error::ReportAssertion(Essentials::Error::AssertLevel::Warning, message, #condition, __FILE__, __LINE__); \
		} \
	} while (false)

	//SoftAssert logs a message to the assert logger, and attempts to connect to a debugger.
	//If no debugger is found, normal execution flow continues.
	#define SOFTASSERT(condition, message) \
	do \
	{ \
		if (!(condition)) \
		{ \
			Essentials::Error::ReportAssertion(Essentials::Error::AssertLevel::SoftAssert, message, #condition, __FILE__, __LINE__); \
			if(IsDebuggerPresent()) \
			{ \
				DebugBreak(); \
			} \
		} \
	} while (false)

	//HardAssert logs a message to the assert logger, attempts to connect to a debugger, and then calls abort
	//If no debugger is found, the process will crash
	#define HARDASSERT(condition, message) \
	do \
	{ \
		if (!(condition)) \
		{ \
			Essentials::Error::ReportAssertion(Essentials::Error::AssertLevel::HardAssert, message, #condition, __FILE__, __LINE__); \
			DebugBreak(); \
			abort(); \
		} \
	} while (false)

    #define STATICASSERT(condition, message) \
    { \
        static_assert((condition), message); \
    } 

	//Critical run time error throws a std::runtime_error with the message parameters;
	#define CRITICAL_RUNTIME_ERROR(condition, message) \
	do \
	{ \
		if (!(condition)) \
		{ \
			throw std::runtime_error(message); \
		} \
	} while (false)

#else
	#define WARNING(condition, message) 
	#define SOFTASSERT(condition, message) 
	#define HARDASSERT(condition, message) 

	#define CRITICAL_RUNTIME_ERROR(condition, message) 

#endif // _DEBUG