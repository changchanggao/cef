//WindowDelegate.cpp
#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
//窗口创建成功
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(browser_view_);
    window->Show();
    browser_view_->RequestFocus();
    window->SetTitle(L"这是我的窗口标题");
    //window->CenterWindow(CefSize(800, 600));
}
//窗口销毁成功
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    browser_view_ = nullptr;
    //CefQuitMessageLoop();
}
//设置窗口位置和大小
CefRect WindowDelegate::GetInitialBounds(CefRefPtr<CefWindow> window) {
    CefRefPtr<CefDisplay> display = CefDisplay::GetPrimaryDisplay();
    CefRect rect = display->GetBounds();
    rect.x = (rect.width - 800) / 2;
    rect.y = (rect.height - 600) / 2;
    rect.width = 800;
    rect.height = 600;
    return rect;
}

bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window)
{
    bool result = true;
    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
    if (browser) {
        result = browser->GetHost()->TryCloseBrowser();
    }
    return result;
}

bool WindowDelegate::IsFrameless(CefRefPtr<CefWindow> window)
{
    return !is_dev_;
}