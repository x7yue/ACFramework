
#include "wrapper_handler_interface.h"
#include "struct_class.h"

extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];
extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_frame[];
extern DWORD acf_cpp_fntable_value[];
extern DWORD acf_cpp_fntable_authcallback[];
extern DWORD acf_cpp_fntable_menucallback[];
extern DWORD acf_cpp_fntable_menuparams[];
extern DWORD acf_cpp_fntable_menumodel[];

namespace wrapper {
 
EnvironmentHandler::EnvironmentHandler(LPVOID callback) : callback_(callback) {}

EnvironmentHandler::~EnvironmentHandler() {
  if (callback_) LocalFree(callback_);
}

void EnvironmentHandler::OnInitialized(AcfRefPtr<AcfEnvironment> env,
                                       bool success) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    env->AddRef();
    IMP_NEWECLASS(TempEnv, env.get(), eClass::m_pVfTable_Environment,
                  acf_cpp_fntable_environment);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, success; 
			push eax;
			push TempEnv;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    env->Release();
  }
}

BrowserHandler::BrowserHandler(LPVOID callback) : callback_(callback) {}

BrowserHandler::~BrowserHandler() {
  if (callback_) LocalFree(callback_);
}

void BrowserHandler::OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnNewWindowRequest(
    AcfRefPtr<AcfBrowser> browser, NewWindowSource source,
    NewWindowDisposition disposition, bool user_gesture,
    AcfRefPtr<AcfNewWindowDelegate> delegate) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    delegate->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempDelegate, delegate.get(), eClass::m_pVfTable_NewWindowDelegate,
                  acf_cpp_fntable_new_window_delegate);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempDelegate;
			movzx eax, user_gesture;
			push eax;
			push disposition;
			push source;
			push TempBrowser;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    delegate->Release();
    browser->Release();
  }
}

void BrowserHandler::OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                           bool show_loading_ui) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, show_loading_ui;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                              NavigationTypes flags) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push flags;
			push TempBrowser;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                                    const AcfString& title) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

		LPSTR pTitle = GetEString(title);
    LPVOID ppTitle = &pTitle;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppTitle;
			push TempBrowser;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                                      const AcfString& address) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    LPSTR pTitle = GetEString(address);
    LPVOID ppTitle = &pTitle;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppTitle;
			push TempBrowser;
			push ecx;
			call[edx + 0x20];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                              bool fullscreen) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, fullscreen;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x24];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadStart(AcfRefPtr<AcfBrowser> browser,
                                 AcfRefPtr<AcfFrame> frame, int transition) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push transition;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x28];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadEnd(AcfRefPtr<AcfBrowser> browser,
                               AcfRefPtr<AcfFrame> frame, const AcfString& url,
                               int http_status_code) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push http_status_code;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x2C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadError(AcfRefPtr<AcfBrowser> browser,
                                 AcfRefPtr<AcfFrame> frame,
                                 const AcfString& url, int error_code) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push error_code;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x30];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnAuthLoginRequest(
    AcfRefPtr<AcfBrowser> browser, bool is_proxy, const AcfString& url,
    const AcfString& scheme, const AcfString& realm, const AcfString& challenge,
    bool is_main_frame, AcfRefPtr<AcfLoginDelegate> delegate) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempCallback, delegate.get(), eClass::m_pVfTable_AuthCallback,
                  acf_cpp_fntable_authcallback);

		LPCSTR pUrl = GetEString(url), pScheme = GetEString(scheme),
           pRealm = GetEString(realm), pChallenge = GetEString(challenge);
		
		LPVOID ppURL = &pUrl, ppScheme = &pScheme, ppRealm = &pRealm,
                       ppChallenge = &pChallenge;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			movzx eax, is_main_frame;
			push eax;
			push ppChallenge;
			push ppRealm;
			push ppScheme;
			push ppURL;
			movzx eax, is_proxy;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x34];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnContextMenuRequest(
    AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfContextMenuParams> menu_params,
    AcfRefPtr<AcfContextMenuModel> menu_model,
    AcfRefPtr<AcfContextMenuCallback> callback) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempParams, menu_params.get(), eClass::m_pVfTable_MenuParams,
                  acf_cpp_fntable_menuparams);
    IMP_NEWECLASS(TempModel, menu_model.get(), eClass::m_pVfTable_MenuModel,
                  acf_cpp_fntable_menumodel);
    IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfTable_MenuCallback,
                  acf_cpp_fntable_menucallback);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempModel;
			push TempParams;
			push TempBrowser;
			push ecx;
			call[edx + 0x38];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnContextMenuExecute(
    AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfContextMenuParams> menu_params,
    int command_id, int event_flags) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempParams, menu_params.get(), eClass::m_pVfTable_MenuParams,
                  acf_cpp_fntable_menuparams);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push event_flags;
			push command_id;
			push TempParams;
			push TempBrowser;
			push ecx;
			call[edx + 0x3C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

}  // namespace wrapper