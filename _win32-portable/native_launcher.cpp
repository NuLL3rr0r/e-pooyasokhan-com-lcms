#define     _UNICODE
#define     UNICODE
#define     WIN32_LEAN_AND_MEAN

#include <string>
#include <cstdlib>
#include <windows.h>
#include <direct.h>
#include <shellapi.h>

using namespace std;

#define     EXECUTABLE_PATH            L".\\app"
#define     EXECUTABLE_NAME            L"eps-desktop.exe"
#define     ERROR_TITLE                L"خطا"
#define     ERROR_MESSAGE              L"امکان اجرای برنامه وجود ندارد!"

int CALLBACK WinMain(
        _In_  HINSTANCE hInstance,
        _In_  HINSTANCE hPrevInstance,
        _In_  LPSTR lpCmdLine,
        _In_  int nCmdShow)
{
    bool hasError = false;

    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if (argc > 0) {
        if (argv[0] != NULL) {
            std::wstring path(argv[0]);
            path = path.substr(0, path.rfind(L"\\") + 1);
            if (_wchdir(path.c_str()) == -1) {
                hasError = true;
            }

            _wchdir(EXECUTABLE_PATH);

            STARTUPINFOW si;
            PROCESS_INFORMATION pi;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            LPWSTR execArgs = NULL;
            if (CreateProcess(EXECUTABLE_NAME, execArgs, NULL, NULL, FALSE,
                              CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            } else {
                hasError = true;
            }
        } else {
            hasError = true;
        }
    } else {
        hasError = true;
    }

    if (hasError) {
        MessageBox(NULL, ERROR_MESSAGE, ERROR_TITLE,
                   MB_OK | MB_ICONERROR | MB_RTLREADING | MB_TOPMOST);
    }

    return 0;
}

