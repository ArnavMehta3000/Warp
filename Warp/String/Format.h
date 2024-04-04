#pragma once
#include <string>
#include <string_view>
#include <format>
#include <array>

namespace Warp
{
    /**
     * @brief Used to format a collection of arguments to narrow string
     * @return Formatted std::string
     * @tparam Args Arguments to format
    */
    template <typename... Args>
	constexpr std::string Format(Args&&... args)
	{
		std::array<char, sizeof...(Args) * 3 + 1> braces{};
		constexpr const char c[4] = "{} ";
		
		for (U32 i = 0u; i != braces.size(); i++)
		{
			braces[i] = c[i % 3];
		}

		braces.back() = '\0';

		return std::vformat(std::string_view(braces.data()), std::make_format_args(args...));
	}

    /**
     * @brief Used to format a collection of arguments to wide string
     * @return Formatted std::wstring
     * @tparam Args Arguments to format
    */
    template <typename... Args>
	constexpr std::wstring FormatW(Args&&... args)
	{
		std::array<wchar_t, sizeof...(Args) * 3 + 1> braces{};
		constexpr const wchar_t c[4] = L"{} ";

		for (U32 i = 0u; i != braces.size(); i++)
		{
			braces[i] = c[i % 3];
		}

		braces.back() = L'\0';

		return std::vformat(std::wstring_view(braces.data()), std::make_wformat_args(args...));
	}
}