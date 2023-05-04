#ifndef ACF_E_HANDLER_H_
#define ACF_E_HANDLER_H_

#include "include/acf_environment.h"
#include "include/acf_browser.h"
#include "include/acf_profile.h"

#include "wrapper_utility.h"

#include <memory>

namespace wrapper {

class EnvironmentHandler : public AcfEnvironmentHandler {
 public:
  EnvironmentHandler(LPVOID callback);
  ~EnvironmentHandler();

 protected:
  void OnInitialized(AcfRefPtr<AcfEnvironment> env, bool success) override;

 private:
  LPVOID callback_;

  IMPLEMENT_REFCOUNTING(EnvironmentHandler);
};

class BrowserHandler : public AcfBrowserHandler {
 public:
  BrowserHandler(LPVOID callback);
  ~BrowserHandler();

 protected:
  void OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) override;
  void OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser, NewWindowSource source,
                          NewWindowDisposition disposition, bool user_gesture,
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
  void OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                bool fullscreen) override;
  void OnAuthLoginRequest(AcfRefPtr<AcfBrowser> browser, bool is_proxy,
                          const AcfString& url, const AcfString& scheme,
                          const AcfString& realm, const AcfString& challenge,
                          bool is_main_frame,
                          AcfRefPtr<AcfLoginDelegate> delegate) override;
  void OnContextMenuRequest(
      AcfRefPtr<AcfBrowser> browser,
      AcfRefPtr<AcfContextMenuParams> menu_params,
      AcfRefPtr<AcfContextMenuModel> menu_model,
      AcfRefPtr<AcfContextMenuCallback> callback) override;
  void OnContextMenuExecute(AcfRefPtr<AcfBrowser> browser,
                            AcfRefPtr<AcfContextMenuParams> menu_params,
                            int command_id, int event_flags) override;
  void OnLoadStart(AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfFrame> frame,
                   int transition) override;
  void OnLoadEnd(AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfFrame> frame,
                 const AcfString& url, int http_status_code) override;
  void OnLoadError(AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfFrame> frame,
                   const AcfString& url, int error_code) override;

 private:
  LPVOID callback_;

  IMPLEMENT_REFCOUNTING(BrowserHandler);
};

}  // namespace wrapper

#endif
