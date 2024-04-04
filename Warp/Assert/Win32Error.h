#pragma once
#include "Common/WarpWin.h"

namespace Warp
{
    /**
	* @brief Get Win32 error string from error code 
	* @param errorCode Error code from GetLastError() or HRESULT to convert
	* @return std::string representation of Win32 error
	*/
	inline std::string GetWin32ErrorString(DWORD errorCode)
	{
		char errorString[MAX_PATH];
		::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
			0,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			errorString,
			MAX_PATH,
			NULL);

		std::string message = "Win32 Error: ";
		message += errorString;
		return message;
	}
}
