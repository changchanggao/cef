//App.cpp
#include "App.h"
#include "include/cef_browser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "WindowDelegate.h"
#include "HttpSchemeFactory.h"
#include "ViewDelegate.h"
#include "PageHandler.h"
//CEF�����������Ļ�����ʼ���ɹ�
void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    CefRegisterSchemeHandlerFactory("https", "liulun", new HttpSchemeFactory());
    std::string url = "https://liulun/index.html?a=123";
    CefBrowserSettings settings;
    CefRefPtr<PageHandler> pageHandler(new PageHandler());
    CefRefPtr<ViewDelegate> viewDelegate(new ViewDelegate());
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, viewDelegate);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view, false));
}
