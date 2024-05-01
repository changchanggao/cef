#include "PageHandler.h"
#include "include/wrapper/cef_helpers.h"
//ҳ�洴���ɹ�
void PageHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	browsers.push_back(browser);
}
//ҳ�漴���ر�
void PageHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	std::list<CefRefPtr<CefBrowser>>::iterator bit = browsers.begin();
	for (; bit != browsers.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			browsers.erase(bit);
			break;
		}
	}
	if (browsers.empty()) {
		CefQuitMessageLoop();
	}
}
