//�ļ���Ϊ��HttpSchemeFactory.h
#pragma once
#include "include/cef_app.h"
class HttpSchemeFactory :public CefSchemeHandlerFactory
{
public:
    HttpSchemeFactory() = default;
    //ɾ����������
    HttpSchemeFactory(const HttpSchemeFactory&) = delete;
    //ɾ����ֵ����
    HttpSchemeFactory& operator=(const HttpSchemeFactory&) = delete;
    //��������ķ�������
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;
private:
    IMPLEMENT_REFCOUNTING(HttpSchemeFactory);
};
