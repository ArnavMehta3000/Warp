#pragma once
#include <string_view>

namespace Warp::Win32
{
	enum class MessageType
	{
		Info,
		Warning,
		Error,
		MESSAGE_TYPE_COUNT
	};

	struct MessageDesc
	{
		MessageType Type;
		std::wstring_view Text;
		std::wstring_view Title;
	};
}