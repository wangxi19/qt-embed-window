#include "widgetcontainer.h"
#include <Windows.h>
#include <QWindow>
#include <TlHelp32.h>
#include <string>
#include <functional>
#include <iostream>
#include <QDebug>

WidgetContainer::WidgetContainer(QWidget *parent)
  :QWidget(parent)
{

}

QWidget *WidgetContainer::createContainer(const QString &iAppName, bool iAutoOpen)
{
    Q_UNUSED(iAutoOpen)
    DWORD procId =(DWORD)findProcessId(iAppName);
    if (procId == 0) {
        return nullptr;
    }

    HANDLE widWindow = nullptr;
    HANDLE *pWidWindow = &widWindow;
    LPARAM curParam;
    char *pParm = (char*)&curParam;
    const char *pProcId = (const char*)&procId;
    const char *pWidWnd = (const char*)&pWidWindow;
    for (int i = 0; i < 8; ++i) {
        if (i < 4) {
            *(pParm + i) = *(pProcId + i);
        } else {
            *(pParm + i) = *(pWidWnd + i - 4);
        }
    }

    WNDENUMPROC EnumWindowsProc =
            [] (HWND wnd, LPARAM lParam) ->BOOL
    {
        const char *pParm = (const char *)&lParam;
        DWORD procId;
        HANDLE *pWidWindow;
        char *pProcId = (char*)&procId;
        char *pWidWnd = (char*)&pWidWindow;
        for (int i = 0; i < 8; ++i) {
            if (i < 4) {
                *(pProcId + i) = *(pParm + i);
            } else {
                *(pWidWnd + i - 4) = *(pParm + i);
            }
        }

        DWORD thProcId = GetWindowThreadProcessId(wnd, nullptr);
        if (thProcId == procId) {
            *(pWidWindow) = (HANDLE)GetWindow(wnd, 0);
        }
        return 1;
    };

    EnumWindows(EnumWindowsProc, curParam);
    HANDLE widWindowAct = FindWindow(L"Notepad++", L"new 1 - Notepad++ [Administrator]");
    QWindow *foreign = QWindow::fromWinId((WId) widWindowAct);
    if (nullptr != foreign) {
        QWidget *container = QWidget::createWindowContainer(foreign);
        return container;
    }
    return nullptr;
}

unsigned long WidgetContainer::findProcessId(const QString &iAppName)
{
    HANDLE hProcessSnap;
//    HANDLE hProcess;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return 0;
    }

    // Now walk the snapshot of processes, and
    // find out the app's handle
    do {
//        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);
//        if (hProcess == nullptr) {
//            continue;
//        }
        if (std::wstring(pe32.szExeFile).find(iAppName.toStdWString()) != std::wstring::npos) {
//            CloseHandle(hProcess);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    return 0;
}
