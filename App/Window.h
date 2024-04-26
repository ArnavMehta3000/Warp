#pragma once
#include <Warp/Common/WarpWin.h>
#include <Warp/Common/StandardTypes.h>
#include <functional>
#include <string_view>
#include <string>

namespace Warp
{
	struct WindowDesc
	{
		std::wstring_view Title = L"Warp Window";
		Types::u32 Width        = 1280;
		Types::u32 Height       = 720;
		DWORD Style             = WS_OVERLAPPEDWINDOW;
	};

	class Window
	{
	public:
		explicit Window(const WindowDesc& desc, HINSTANCE hInstance);
		~Window();

		void SetTitle(std::wstring_view title);
		void SetMessageHandler(std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> handler);
		void Show() const;
		void Close();
		bool WantsToClose() const;


		LRESULT	MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		inline HWND GetHandle() const { return m_hWnd; }
		inline constexpr bool IsValid() const { return m_hWnd != nullptr; }
		inline Types::u32 GetWidth() const { return m_width; }
		inline Types::u32 GetHeight() const { return m_height; }

	private:
		std::wstring m_title;
		Types::u32   m_width;
		Types::u32   m_height;
		HWND         m_hWnd;
		HINSTANCE    m_hInstance;
		bool         m_isRunning;
		
		std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> m_messageHandler;
	};
}