#pragma once
#include "DialogDesc.h"
#include <future>

namespace Warp::Win32
{
	void ShowMessageBox(const MessageDesc& desc);
	
	std::wstring ShowOpenDialog(std::wstring_view filter, void* hWnd);
	[[nodiscard]] std::future<std::wstring> ShowOpenDialogAsync(std::wstring_view filter, void* hWnd);
	
	std::wstring ShowSaveDialog(std::wstring_view filter, void* hWnd);
	[[nodiscard]] std::future<std::wstring> ShowSaveDialogAsync(std::wstring_view filter, void* hWnd);
}