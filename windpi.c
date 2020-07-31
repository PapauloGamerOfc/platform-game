#include <windows.h>

void windpi_setaware()
{
    typedef enum PROCESS_DPI_AWARENESS {
        PROCESS_DPI_UNAWARE = 0,
        PROCESS_SYSTEM_DPI_AWARE = 1,
        PROCESS_PER_MONITOR_DPI_AWARE = 2
    } PROCESS_DPI_AWARENESS;

    BOOL(WINAPI *SetProcessDPIAware)(void) = NULL;
    HRESULT(WINAPI *SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS dpiAwareness) = NULL;

    HINSTANCE userDLL; // Vista and later
    HINSTANCE shcoreDLL; // Windows 8.1 and later

    userDLL = LoadLibrary("USER32.DLL");
    if (userDLL) {
        SetProcessDPIAware = (BOOL(WINAPI *)(void)) GetProcAddress(userDLL, "SetProcessDPIAware");
    }

    shcoreDLL = LoadLibrary("SHCORE.DLL");
    if (shcoreDLL) {
        SetProcessDpiAwareness = (HRESULT(WINAPI *)(PROCESS_DPI_AWARENESS)) GetProcAddress(shcoreDLL, "SetProcessDpiAwareness");
    }

    if (SetProcessDpiAwareness) {
    /* Try Windows 8.1+ version */
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    }
    else if (SetProcessDPIAware) {
    /* Try Vista - Windows 8 version.
    This has a constant scale factor for all monitors.
    */
        SetProcessDPIAware();
    }
}
