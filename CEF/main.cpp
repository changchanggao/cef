#include <windows.h>
#include "App.h"
//����Ӧ�õ���ں���
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    //CefEnableHighDPISupport();
    CefMainArgs main_args(hInstance);
    CefSettings settings;
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    CefRefPtr<App> app(new App());
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}