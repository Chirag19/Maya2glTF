#include "externals.h"
#include "OutputWindow.h"
#include "MayaException.h"

#ifdef WIN32

WindowFinder::WindowFinder(const char* windowStyleName, HWND parentWindowHandle)
    : styleName(windowStyleName)
    , windowHandle(nullptr)
{
    EnumWindows(Find, reinterpret_cast<LPARAM>(this));
}

bool WindowFinder::Find(HWND hWnd)
{
    DWORD processId = 0;
    GetWindowThreadProcessId(hWnd, &processId);

    if (processId == GetCurrentProcessId())
    {
        char windowClass[256];
        RealGetWindowClassA(hWnd, windowClass, sizeof(windowClass));
        if (strcmp(windowClass, styleName) == 0)
        {
            windowHandle = hWnd;
        }
        else
        {
            EnumChildWindows(hWnd, Find, reinterpret_cast<LPARAM>(this));
        }
    }

    return windowHandle == nullptr;
}

BOOL WindowFinder::Find(HWND hWnd, LPARAM param)
{
    return reinterpret_cast<WindowFinder*>(param)->Find(hWnd);
}


OutputWindow::OutputWindow()
    : m_editControlHandle(nullptr)
{
    const auto outputWindowHandle = WindowFinder("mayaConsole", nullptr).windowHandle;

    if (!outputWindowHandle)
    {
        MayaException::printError("Failed to find mayaConsole in output window");
        return;
    }

    m_editControlHandle = WindowFinder("Edit", outputWindowHandle).windowHandle;
    if (!m_editControlHandle)
    {
        MayaException::printError("Failed to find edit control in output window");
        return;
    }
}

void OutputWindow::clear() const
{
    if (m_editControlHandle)
    {
        SetWindowText(m_editControlHandle, "");
    }
}

#else

OutputWindow::OutputWindow()
{
}

void OutputWindow::Clear()
{
}

#endif