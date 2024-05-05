#include "PageHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include <winternl.h>

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

const std::string getOSVersion()
{
	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osInfo;
	std::string result;
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle(L"ntdll"), "RtlGetVersion");
	if (nullptr != RtlGetVersion) {
		osInfo.dwOSVersionInfoSize = sizeof osInfo;
		RtlGetVersion(&osInfo);
		result = std::to_string(osInfo.dwMajorVersion) + "." + std::to_string(osInfo.dwMinorVersion) + "." + std::to_string(osInfo.dwBuildNumber);
	}
	return result;
}

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

void PageHandler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions)
{
	CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
	if (browser_view)
	{
		CefRefPtr<CefWindow> window = browser_view->GetWindow();
		if (window) {
			window->SetDraggableRegions(regions);
		}
	}
}

bool PageHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	CEF_REQUIRE_UI_THREAD();
	std::string messageName = message->GetName();
	std::vector<std::string> arr = split(messageName, '_');
	if (arr.at(0) == "window") {
		CefRefPtr<CefBrowserView> browserView = CefBrowserView::GetForBrowser(browser);
		CefRefPtr<CefWindow> window = browserView->GetWindow();
		if (arr.at(1) == "minimize") {
			window->Minimize();
		}
		else if (arr.at(1) == "maximize") {
			window->Maximize();
		}
		else if (arr.at(1) == "close") {
			window->Close();
		}
		else if (arr.at(1) == "restore") {
			window->Restore();
		}
	}
	else if (arr.at(0) == "system") {
		// messageName是在进入OnProcessMessageReceived方法时就通过如下代码获得了，它就是渲染进程发来的消息名
		// std::string messageName = message->GetName();
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(messageName);
		CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
		if (arr.at(1) == "getOSVersion") {
			std::string version = getOSVersion();
			msgArgs->SetString(0, version);
		}
		frame->SendProcessMessage(PID_RENDERER, msg);
	}

	return true;
}
