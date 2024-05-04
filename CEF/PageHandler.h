#pragma once
#include "include/cef_app.h"
#include <list>
class PageHandler :public CefClient, public CefLifeSpanHandler, public CefJSDialogHandler
    , public CefContextMenuHandler
{
public:
    PageHandler() = default;
    //获取LifeSpanHandler对象
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override { return this; }
    CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; }

    //页面创建成功
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    //页面即将关闭
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, 
        CefRefPtr<CefJSDialogCallback> callback) override;
    virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;
    virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags) override;
private:
    IMPLEMENT_REFCOUNTING(PageHandler);
    std::list<CefRefPtr<CefBrowser>> browsers;
};
