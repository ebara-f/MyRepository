#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <ShlObj.h>
#include <vector>

#pragma comment(lib, "shell32.lib")

// ============================================================
// プロセス存在確認
// ============================================================
bool IsProcessRunning(const std::wstring& exeName)
{
    HANDLE hSnapshot =
        CreateToolhelp32Snapshot(
            TH32CS_SNAPPROCESS,
            0);

    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W pe = {};
    pe.dwSize = sizeof(pe);

    if (Process32FirstW(hSnapshot, &pe))
    {
        do
        {
            if (_wcsicmp(
                pe.szExeFile,
                exeName.c_str()) == 0)
            {
                CloseHandle(hSnapshot);
                return true;
            }

        } while (Process32NextW(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);

    return false;
}

// ============================================================
// ini読み込み
// ============================================================
std::wstring ReadIni(const wchar_t* key)
{
    wchar_t programData[MAX_PATH] = {};

    SHGetFolderPathW(
        nullptr,
        CSIDL_COMMON_APPDATA,
        nullptr,
        0,
        programData);

    std::wstring iniPath =
        std::wstring(programData) +
        L"\\Kosakalab\\Kosaka CMM\\Inifiles\\launcher.ini";

    wchar_t value[1024] = {};

    GetPrivateProfileStringW(
        L"APP",
        key,
        L"",
        value,
        1024,
        iniPath.c_str());

    return value;
}

// ============================================================
// 標準ユーザー権限で起動
// ============================================================
bool LaunchProcess(
    const std::wstring& exe,
    const std::wstring& args)
{
    STARTUPINFOW si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_MINIMIZE;

    // コマンドライン作成
    std::wstring cmdLine =
        L"\"" + exe + L"\" " + args;

    // CreateProcessW は writable buffer 必須
    std::vector<wchar_t> buffer(
        cmdLine.begin(),
        cmdLine.end());

    buffer.push_back(L'\0');

    BOOL result =
        CreateProcessW(
            nullptr,
            buffer.data(),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi);

    if (result)
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return result == TRUE;
}

// ============================================================
// WinMain
// ============================================================
int WINAPI WinMain(
    HINSTANCE,
    HINSTANCE,
    LPSTR,
    int)
{
    // ========================================================
    // 多重起動防止
    // ========================================================
    HANDLE hMutex =
        CreateMutexW(
            nullptr,
            TRUE,
            L"KOSAKALAB_LAUNCHER_MUTEX");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return 0;
    }

    // ========================================================
    // ini読み込み
    // ========================================================
    std::wstring myApp =
        ReadIni(L"MY_APP");

    std::wstring myArgs =
        ReadIni(L"MY_ARGS");

    std::wstring otherApp =
        ReadIni(L"OTHER_APP");

    // ========================================================
    // K-CMM.exe
    // ========================================================
    if (!IsProcessRunning(L"K-CMM.exe"))
    {
        LaunchProcess(
            myApp,
            myArgs);
    }

    // ========================================================
    // iminspect.exe
    // ========================================================
    if (!IsProcessRunning(L"iminspect.exe"))
    {
        LaunchProcess(
            otherApp,
            L"");
    }

    // ========================================================
    // Cleanup
    // ========================================================
    if (hMutex)
    {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
    }

    return 0;
}