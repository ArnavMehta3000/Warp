#include "Dialogs.h"
#include <Warp/Common/WarpWin.h>
#include <commdlg.h>

namespace Warp::Win32
{
	void ShowMessageBox(const MessageDesc& desc)
	{
		UINT flags = MB_APPLMODAL | MB_SETFOREGROUND | MB_OK;

		// Set icon based on type
		if (desc.Type == MessageType::Info)
			flags |= MB_ICONINFORMATION;
		else if (desc.Type == MessageType::Warning)
			flags |= MB_ICONWARNING;
		else if (desc.Type == MessageType::Error)
			flags |= MB_ICONERROR;

		MessageBox(nullptr, desc.Text.data(), desc.Title.data(), flags);
	}

	std::wstring ShowOpenDialog(std::wstring_view filter, void* hWnd)
	{
		OPENFILENAME ofn;
		WCHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize   = sizeof(OPENFILENAME);
		ofn.hwndOwner     = (HWND)hWnd;
		ofn.lpstrFile     = szFile;
		ofn.nMaxFile      = sizeof(szFile);
		ofn.lpstrFilter   = filter.data();
		ofn.nFilterIndex  = 1;
		ofn.Flags         = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileName(&ofn))
		{
			return ofn.lpstrFile;
		}

		return std::wstring();
	}

	std::future<std::wstring> ShowOpenDialogAsync(std::wstring_view filter, void* hWnd)
	{
		return std::async(std::launch::async, [filter, hWnd] {return ShowOpenDialog(filter, hWnd); });
	}

	std::wstring ShowSaveDialog(std::wstring_view filter, void* hWnd)
	{
		OPENFILENAME ofn;
		WCHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = (HWND)hWnd;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter.data();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn))
		{
			return ofn.lpstrFile;
		}

		return std::wstring();
	}

	std::future<std::wstring> ShowSaveDialogAsync(std::wstring_view filter, void* hWnd)
	{
		return std::async(std::launch::async, [filter, hWnd] {return ShowSaveDialog(filter, hWnd); });
	}

}