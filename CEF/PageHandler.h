#pragma once
#include "include/cef_app.h"
#include <list>
class PageHandler :public CefClient, public CefLifeSpanHandler
{
public:
    PageHandler() = default;
    //��ȡLifeSpanHandler����
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    //ҳ�洴���ɹ�
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    //ҳ�漴���ر�
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
private:
    IMPLEMENT_REFCOUNTING(PageHandler);
    std::list<CefRefPtr<CefBrowser>> browsers;
};
