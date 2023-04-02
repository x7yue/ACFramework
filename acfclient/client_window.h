#ifndef ACF_CLIENT_WINDOW_H_
#define ACF_CLIENT_WINDOW_H_

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "include/acf_browser.h"

namespace acfclient {

extern std::vector<AcfRefPtr<AcfBrowser>> g_browsers;

class Window : public AcfBrowserHandler {
 public:
  Window(AcfRefPtr<AcfEnvironment> env,
         HINSTANCE instance,
         RECT* initial_rect,
         AcfRefPtr<AcfNewWindowDelegate> new_window = nullptr);
  ~Window() override;

  // Interface
  void Show();
  void Hide();

  HWND GetHandle();
  HWND GetHandle() const;

  HWND GetEditHandle() { return edit_control_; }

  RECT GetBrowserBound();
  void SetBrowser(HWND handle);

  // event
  void OnCreate(HWND window);
  void OnSize(HWND window);
  bool OnCommand(UINT id);
  void OnFocus();
  void OnClose();
  void CreateMenu();

  // BrowserHandler override
  void OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) override;
  void OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser,
                          NewWindowSource source,
                          NewWindowDisposition disposition,
                          bool user_gesture,
                          AcfRefPtr<AcfNewWindowDelegate> delegate) override;
  void OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) override;
  void OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                             bool show_loading_ui) override;
  void OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                NavigationTypes flags) override;
  void OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                      const AcfString& title) override;
  void OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                        const AcfString& address) override;
  void OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser, bool fullscreen) override;
  
  AcfBrowser* browser_weak_ptr_ = nullptr;

 private:
  void RegisterWindowClass();
  static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam,
                                      LPARAM lParam);

  // host
  HWND window_;
  HINSTANCE instance_;

  // control
  HWND back_button_;
  HWND forward_button_;
  HWND reload_button_;
  HWND stop_button_;
  [[maybe_unused]] HWND more_button_;
  HWND edit_control_;
  [[maybe_unused]] HWND nav_button_;

  HMENU more_menu_;

  HWND browser_window_ = nullptr;
  
  // Pending new browser
  AcfRefPtr<AcfNewWindowDelegate> new_browser_delegate_;

 IMPLEMENT_REFCOUNTING(Window);
};

}  // namespace acfclient

#endif