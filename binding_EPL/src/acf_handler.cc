#include "acf_handler.h"
#include "acf_Class.h"

namespace wrapper {
 
EnvironmentHandler::EnvironmentHandler(LPVOID callback) : callback_(callback) {}

EnvironmentHandler::~EnvironmentHandler() {
  if (callback_) LocalFree(callback_);
}

void EnvironmentHandler::OnEnvironmentInitialized(
    AcfRefPtr<AcfEnvironment> env) {
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

void EnvironmentHandler::OnEnvironmentDestroyed(AcfRefPtr<AcfEnvironment> env) {
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
			push TempEnv;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    env->Release();
  }
}

ProfileHandler::ProfileHandler(LPVOID callback) : callback_(callback) {}

ProfileHandler::~ProfileHandler() {
  if (callback_) LocalFree(callback_);
}

void ProfileHandler::OnProfileCreated(AcfRefPtr<AcfProfile> profile) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempProfile;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
  }
}

void ProfileHandler::OnProfileDestroyed(AcfRefPtr<AcfProfile> profile) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempProfile;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
  }
}

void ProfileHandler::OnProfileRemoveDataCompleted(AcfRefPtr<AcfProfile> profile,
                                                  AcfUserData token) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push token;
			push TempProfile;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
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

}  // namespace wrapper