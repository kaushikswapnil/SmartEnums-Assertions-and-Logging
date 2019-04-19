#pragma once
#include "LogPolicy.h"
#include <fstream>
#include "Assertion.h"

class FileLogPolicy : public ILogPolicy
{
private:
	std::ofstream outStream;
public:
	FileLogPolicy() = default;
	~FileLogPolicy() = default;

	void OpenOStream(const std::string& ostreamName)
	{
		//HARDASSERT(!outStream.is_open(), "Trying to open file stream that is already open.");
		outStream.open(ostreamName, std::ios_base::out);
		//CRITICAL_RUNTIME_ERROR(outStream.is_open(), "Unable to open log file for writing."); //Crash if the file is not found
	}

	void CloseOStream()
	{
		//HARDASSERT(outStream.is_open(), "Trying to close a file that is not open.");
		outStream.close();
	}

	void Write(const std::string& message)
	{
		outStream << message << std::endl;
	}

	/*void OpenOStream(const std::string& ostreamName) override;
	void CloseOStream() override;
	void Write(const std::string& message) override;*/
};

