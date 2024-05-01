//文件名为：HttpSchemeFactory.h
#pragma once
#include "include/cef_app.h"
class HttpSchemeFactory :public CefSchemeHandlerFactory
{
public:
    HttpSchemeFactory() = default;
    //删除拷贝函数
    HttpSchemeFactory(const HttpSchemeFactory&) = delete;
    //删除赋值函数
    HttpSchemeFactory& operator=(const HttpSchemeFactory&) = delete;
    //处理请求的方法定义
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;
private:
    IMPLEMENT_REFCOUNTING(HttpSchemeFactory);
};
