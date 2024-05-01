//App.cpp
#include "App.h"
#include "include/cef_browser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "WindowDelegate.h"
#include "HttpSchemeFactory.h"
//CEF主进程上下文环境初始化成功
void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    CefRegisterSchemeHandlerFactory("https", "liulun", new HttpSchemeFactory());
    std::string url = "https://liulun/index.html?a=123";
    CefBrowserSettings settings;
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(nullptr, url, settings, nullptr, nullptr, nullptr);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view));
}
