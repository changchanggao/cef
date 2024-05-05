#include "Render.h"

void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> globalObject = context->GetGlobal();
    CefRefPtr<CefV8Value> nativeCall = CefV8Value::CreateFunction("nativeCall", new V8Handler());
    globalObject->SetValue("nativeCall", nativeCall, V8_PROPERTY_ATTRIBUTE_READONLY);
}

void Renderer::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
    registrar->AddCustomScheme("my", CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_CORS_ENABLED);
}
