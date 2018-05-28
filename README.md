# qt-embed-window
**To embed external exe window into qt application**

**1. 平台**
  `windows + (qt5.6+) + lib:luser32 + Microsoft Visual C++ Compiler 14.0 (x86) + UNICODE`

**2. 准备**
  `配置.exe文件目录的路径到环境变量'path'`

**3. 实现**
    1. 指定程序名(string) iAppName
    2. 查询进程ID(DWORD) procId, 使用'CreateToolhelp32Snapshot'
    3. 如果进程ID(DWORD) procId为空, 则创建该进程, 使用'CreateProcess'
    4. 等待该进程窗口被创建, 目前使用'Sleep', 有更好的方法
    5. Enum窗口, 找寻进程ID与 procId相等的窗口, 获取其句柄 (HWND) wndHandle, 使用'EnumWindows'
    6. 创建一个(QWindow*) foregin去handle窗口wndHandle, 使用'QWindow::fromWinId'
    7. 为这个QWindow创建一个(QWidget*)container, 使用'QWidget::createWindowContainer'
    8. 返回container

**4.源码**
https://github.com/wangxi19/qt-embed-window.git


**1. PlatForm**
  `windows + (qt5.6+) + lib:luser32 + Microsoft Visual C++ Compiler 14.0 (x86) + UNICODE`

**2. prepare**
  `configure .exe file's directory path to 'path'`

**3. do**
    1. specify the program name(string) iAppName
    2. query process id (DWORD) procId, use'CreateToolhelp32Snapshot'
    3. if process id (DWORD) procId is empty, then create the process, use'CreateProcess'
    4. wait for the process's window has been created, use'Sleep', there is a better way
    5. Enumera each window, find out the window that it's process id equal to procId, get it's (HWND) wndHandle, use 'EnumWindows'
    6. create a (QWindow*) foregin, use it to handle the window wndHandle, use 'QWindow::fromWinId'
    7. create a (QWidget*)container for the QWindow, use 'QWidget::createWindowContainer'
    8. return container

**4. source code**
https://github.com/wangxi19/qt-embed-window.git
