// WindowDelegate.h
#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view, 
        bool is_dev) : browser_view_(browser_view), is_dev_(is_dev) {};
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
private:
    CefRefPtr<CefBrowserView> browser_view_;
    bool is_dev_ = false;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

