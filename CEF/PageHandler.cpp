#include "PageHandler.h"
#include "include/wrapper/cef_helpers.h"
//页面创建成功
void PageHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	browsers.push_back(browser);
}
//页面即将关闭
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

bool PageHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload,
	CefRefPtr<CefJSDialogCallback> callback) {
	auto hwnd = browser->GetHost()->GetWindowHandle();
	int msgboxID = MessageBox(hwnd, L"您编辑的内容尚未保存.\n确定要关闭窗口吗?", L"系统提示", MB_ICONEXCLAMATION | MB_OKCANCEL);
	if (msgboxID == IDOK) {
		callback->Continue(true, CefString());
	}
	else {
		callback->Continue(false, CefString());
	}
	return true;
}

void PageHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
	model->Clear();
	model->AddItem(MENU_ID_USER_FIRST, L"打开开发者调试工具");
	CefRefPtr<CefMenuModel> subModel = model->AddSubMenu(MENU_ID_USER_FIRST + 1, L"这是一个包含子菜单的测试菜单");
	subModel->AddItem(MENU_ID_USER_FIRST + 2, L"这是子菜单1");
	subModel->AddItem(MENU_ID_USER_FIRST + 3, L"这是子菜单2");
	model->AddSeparator();
	model->AddCheckItem(MENU_ID_USER_FIRST + 4, L"这是一个包含复选框的菜单");
	model->SetChecked(MENU_ID_USER_FIRST + 4, true);
	model->AddRadioItem(MENU_ID_USER_FIRST + 5, L"这是一个包含复选框的菜单", 888);
	model->AddRadioItem(MENU_ID_USER_FIRST + 6, L"这是一个包含单选框的菜单", 888);
	model->SetChecked(MENU_ID_USER_FIRST + 6, true);
}


bool PageHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags)
{
	switch (command_id)
	{
	case MENU_ID_USER_FIRST: {
		CefBrowserSettings browserSettings;
		CefWindowInfo windowInfo;
		CefPoint mousePoint(params->GetXCoord(), params->GetYCoord());
		browser->GetHost()->ShowDevTools(windowInfo, this, browserSettings, mousePoint);
		break;
	}

	default: {
		std::wstring msg = L"你点击的标签ID：" + std::to_wstring(command_id);
		MessageBox(NULL, (LPWSTR)msg.c_str(), L"系统提示", MB_ICONEXCLAMATION | MB_OKCANCEL);
		break;
	}
	}
	return true;
}
