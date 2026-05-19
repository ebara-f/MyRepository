#include <windows.h>
#include <shellapi.h>
#include <tlhelp32.h>
#include <string>
#include <ShlObj.h>

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")

// ============================================================
// 管理者権限チェック
// ============================================================
bool IsRunAsAdmin()
{
    BOOL isAdmin = FALSE;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;

    PSID adminGroup = nullptr;

    if (AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &adminGroup))
    {
        CheckTokenMembership(
            nullptr,
            adminGroup,
            &isAdmin);

        FreeSid(adminGroup);
    }

    return isAdmin == TRUE;
}

// ============================================================
// 自身を管理者再起動
// ============================================================
void RelaunchAsAdmin()
{
    wchar_t exePath[MAX_PATH] = {};

    GetModuleFileNameW(
        nullptr,
        exePath,
        MAX_PATH);

    SHELLEXECUTEINFOW sei = {};

    sei.cbSize = sizeof(sei);
    sei.lpVerb = L"runas";
    sei.lpFile = exePath;
    sei.nShow = SW_HIDE;

    ShellExecuteExW(&sei);
}

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
// EXEフォルダ取得
// ============================================================
std::wstring GetExeDirectory()
{
    wchar_t path[MAX_PATH] = {};

    GetModuleFileNameW(
        nullptr,
        path,
        MAX_PATH);

    std::wstring dir = path;

    size_t pos = dir.find_last_of(L"\\");

    if (pos != std::wstring::npos)
    {
        dir = dir.substr(0, pos);
    }

    return dir;
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
// 管理者起動
// ============================================================
bool LaunchAdmin(
    const std::wstring& exe,
    const std::wstring& args)
{
    SHELLEXECUTEINFOW sei = {};

    sei.cbSize = sizeof(sei);
    sei.lpVerb = L"runas";
    sei.lpFile = exe.c_str();
    sei.lpParameters = args.c_str();
    sei.nShow = SW_MINIMIZE;

    return ShellExecuteExW(&sei);
}

// ============================================================
// Explorer.exe の Token 取得
// ============================================================
HANDLE GetExplorerToken()
{
    HWND hwnd = GetShellWindow();

    if (!hwnd)
        return nullptr;

    DWORD pid = 0;

    GetWindowThreadProcessId(hwnd, &pid);

    if (pid == 0)
        return nullptr;

    HANDLE hProcess =
        OpenProcess(
            PROCESS_QUERY_INFORMATION,
            FALSE,
            pid);

    if (!hProcess)
        return nullptr;

    HANDLE hToken = nullptr;

    if (!OpenProcessToken(
        hProcess,
        TOKEN_DUPLICATE |
        TOKEN_ASSIGN_PRIMARY |
        TOKEN_QUERY,
        &hToken))
    {
        CloseHandle(hProcess);
        return nullptr;
    }

    CloseHandle(hProcess);

    HANDLE hPrimaryToken = nullptr;

    if (!DuplicateTokenEx(
        hToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityImpersonation,
        TokenPrimary,
        &hPrimaryToken))
    {
        CloseHandle(hToken);
        return nullptr;
    }

    CloseHandle(hToken);

    return hPrimaryToken;
}

// ============================================================
// 完全通常ユーザー権限起動
// ============================================================
bool LaunchAsStandardUser(
    const std::wstring& exe)
{
    HANDLE hToken =
        GetExplorerToken();

    if (!hToken)
        return false;

    STARTUPINFOW si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);

    wchar_t cmdLine[1024] = {};

    wcscpy_s(cmdLine, exe.c_str());

    BOOL result =
        CreateProcessWithTokenW(
            hToken,
            LOGON_WITH_PROFILE,
            nullptr,
            cmdLine,
            CREATE_NEW_CONSOLE,
            nullptr,
            nullptr,
            &si,
            &pi);

    CloseHandle(hToken);

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
    // Mutex
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
    // 管理者昇格
    // ========================================================
    if (!IsRunAsAdmin())
    {
        RelaunchAsAdmin();
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
        LaunchAdmin(
            myApp,
            myArgs);
    }

    // ========================================================
    // iminspect.exe
    // ========================================================
    if (!IsProcessRunning(L"iminspect.exe"))
    {
        LaunchAsStandardUser(otherApp);
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