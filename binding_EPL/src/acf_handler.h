#ifndef ACF_E_HANDLER_H_
#define ACF_E_HANDLER_H_

#include "include/acf_environment.h"
#include "include/acf_browser.h"
#include "include/acf_profile.h"

#include "acf_Util.h"

namespace wrapper {

class EnvironmentHandler : public AcfEnvironmentHandler {
 public:
  EnvironmentHandler(LPVOID callback);
  ~EnvironmentHandler();

 protected:
  void OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) override;
  void OnEnvironmentDestroyed(AcfRefPtr<AcfEnvironment> env) override;

 private:
  LPVOID callback_;

  IMPLEMENT_REFCOUNTING(EnvironmentHandler);
};

class ProfileHandler : public AcfProfileHandler {
 public:
  ProfileHandler(LPVOID callback);
  ~ProfileHandler();

 protected:
  void OnProfileCreated(AcfRefPtr<AcfProfile> profile) override;
  void OnProfileDestroyed(AcfRefPtr<AcfProfile> profile) override;

 private:
  LPVOID callback_;

  IMPLEMENT_REFCOUNTING(ProfileHandler);
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

 private:
  LPVOID callback_;

  IMPLEMENT_REFCOUNTING(BrowserHandler);
};

}  // namespace wrapper

#endif
