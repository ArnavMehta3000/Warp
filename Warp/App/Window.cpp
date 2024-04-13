#include "Window.h"
#include <Warp/Assert/Win32Error.h>
#include <Warp/String/StringConverter.h>
#include <assert.h>

namespace Warp
{
	using namespace Types;

	static const std::wstring s_windowClassName = L"WarpApp";

	Window::Window(const WindowDesc& desc, HINSTANCE hInstance)
		: m_title(desc.Title)
		, m_width(desc.Width)
		, m_height(desc.Height)
		, m_hWnd(nullptr)
		, m_hInstance(hInstance)
		, m_isRunning(false)
	{
		WNDCLASSEX wcx{};
		wcx.cbSize        = sizeof(wcx);
		wcx.style         = CS_HREDRAW | CS_VREDRAW;
		wcx.hInstance     = m_hInstance;
		wcx.lpfnWndProc   = WndProc;
		wcx.lpszClassName = s_windowClassName.c_str();
		wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcx.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);

		::RegisterClassExW(&wcx);

		// Get window centered position
		RECT desktopRect{};
		::GetWindowRect(::GetDesktopWindow(), &desktopRect);
		i32 posX = (desktopRect.right / 2) - (m_width / 2);
		i32 posY = (desktopRect.bottom / 2) - (m_height / 2);

		m_hWnd = ::CreateWindowEx(
			0,
			s_windowClassName.c_str(),
			m_title.c_str(),
			desc.Style,
			posX, posY,
			m_width, m_height,
			nullptr,
			nullptr,
			m_hInstance,
			this
		);

		assert(m_hWnd && "Failed to create window");

		if (!m_hWnd)
			return;
		
		RECT windowRect{};
		::AdjustWindowRect(&windowRect, desc.Style, FALSE);
		m_width  = windowRect.right - windowRect.left;
		m_height = windowRect.bottom - windowRect.top;
		
		m_isRunning = true;
		::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOSIZE);
	}

	Window::~Window()
	{

		::DestroyWindow(m_hWnd);
		::UnregisterClass(s_windowClassName.c_str(), m_hInstance);
	}

	void Window::SetTitle(std::wstring_view title)
	{
		m_title = title;
		::SetWindowTextW(m_hWnd, m_title.c_str());
	}

	void Window::SetMessageHandler(std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> handler)
	{
		m_messageHandler = handler;
	}

	void Window::Show() const
	{
		::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}

	void Window::Close()
	{
		m_isRunning = false;
	}

	bool Window::WantsToClose() const
	{
		// If not running, window either failed to create or was closed
		if (!m_isRunning)
		{
			return true;
		}

		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);

			if (msg.message == WM_QUIT)
			{
				return true;
			}
		}
		return false;
	}

	LRESULT WINAPI Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_NCCREATE:
		{
			LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			Window* pObj = reinterpret_cast<Window*>(pCreateStruct->lpCreateParams);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		}

		Window* pObj = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (pObj)
			return pObj->MessageHandler(hWnd, uMsg, wParam, lParam);
		else
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			::PostQuitMessage(0);
			break;

		case WM_DESTROY:
			::DestroyWindow(m_hWnd);
			break;
		}

		// Custom message handler assigned, use it
		if (m_messageHandler)
		{
			return m_messageHandler(hWnd, uMsg, wParam, lParam);
		}

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}