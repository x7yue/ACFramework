#ifndef ACF_BROWSER_H_
#define ACF_BROWSER_H_

#include <wtypes.h>

#include "include/acf_environment.h"
#include "include/acf_frame.h"

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_string_list.h"
#include "include/internal/acf_types.h"

class AcfEnvironment;
class AcfBrowser;
class AcfNewWindowDelegate;
class AcfProfile;
class AcfFrame;

///
/// Browser event list handler model
///
/*--acf(source=client)--*/
class AcfBrowserHandler : public virtual AcfBaseRefCounted {
 public:
  typedef acf_new_window_source_t NewWindowSource;
  typedef acf_new_window_disposition_t NewWindowDisposition;
  typedef acf_navigation_types_t NavigationTypes;

  ///
  /// Called when browser has been initialized from environment.
  ///
  /*--acf()--*/
  virtual void OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {}

  ///
  /// The browser will open a new Browser as NewWindow
  ///
  /*--acf()--*/
  virtual void OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser,
                                  NewWindowSource source,
                                  NewWindowDisposition disposition,
                                  bool user_gesture,
                                  AcfRefPtr<AcfNewWindowDelegate> delegate) {}

  ///
  /// When the browser was sured to be destroyed,
  /// the browser will call this event.
  ///
  /*--acf()--*/
  virtual void OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {}

  ///
  /// Loading state changed (async)
  ///
  /*--acf()--*/
  virtual void OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                     bool show_loading_ui) {}

  ///
  /// Navigation state changed (title url icon historical)
  ///
  /*--acf()--*/
  virtual void OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                        NavigationTypes flags) {}

  ///
  /// Title bar info changed
  ///
  /*--acf()--*/
  virtual void OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                              const AcfString& title) {}

  ///
  /// Address bar info changed
  ///
  /*--acf()--*/
  virtual void OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                                const AcfString& address) {}

  ///
  /// notify fullscreen state changed
  ///
  /*--acf()--*/
  virtual void OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                        bool fullscreen) {}
};

///
/// ACF's browser object host,
/// in fact a browser was a window in chromium with tabs control.
///
/*--acf(source=library)--*/
class AcfBrowser : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Is same object
  ///
  /*--acf()--*/
  virtual bool IsSame(AcfRefPtr<AcfBrowser> that) = 0;

  ///
  /// Get browser event handler
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfBrowserHandler> GetHandler() = 0;

  ///
  /// Get browser create's sign.
  ///
  /*--acf()--*/
  virtual AcfUserData GetUserData() = 0;

  ///
  /// Get parent environment
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfEnvironment> GetEnvironment() = 0;

  ///
  /// Close browser, it will call browser close event (or unlaod dialog)
  ///
  /*--acf()--*/
  virtual void Close(bool force) = 0;

  ///
  /// Get browser window handle
  ///
  /*--acf()--*/
  virtual AcfWindowHandle GetWindowHandle() = 0;

  ///
  /// Get delegate status
  ///
  /*--acf()--*/
  virtual bool IsValid() = 0;

  ///
  /// Browser navigation entry controller: can go back
  ///
  /*--acf()--*/
  virtual bool CanGoBack() = 0;

  ///
  /// Browser navigation entry controller: can go forward
  ///
  /*--acf()--*/
  virtual bool CanGoForward() = 0;

  ///
  /// Browser navigation entry controller: go back
  ///
  /*--acf()--*/
  virtual void GoBack() = 0;

  ///
  /// Browser navigation entry controller: go forward
  ///
  /*--acf()--*/
  virtual void GoForward() = 0;

  ///
  /// Browser navigation entry controller: reload
  ///
  /*--acf()--*/
  virtual void Reload(bool ignore_cache) = 0;

  ///
  /// Browser navigation entry controller: stop loading
  ///
  /*--acf()--*/
  virtual void Stop() = 0;

  ///
  /// Browser navigation entry controller: loading
  ///
  /*--acf()--*/
  virtual bool IsLoading() = 0;

  ///
  /// Navigate to target url (Main frame)
  ///
  /*--acf()--*/
  virtual void LoadURL(const AcfString& url) = 0;

  ///
  /// Get current url
  ///
  /*--acf()--*/
  virtual AcfString GetURL() = 0;
  
  ///
  /// Get title
  ///
  /*--acf()--*/
  virtual AcfString GetTitle() = 0;

  ///
  /// Focus to native widget
  ///
  /*--acf()--*/
  virtual void Focus() = 0;

  ///
  /// Set/Get window visible
  ///
  /*--acf()--*/
  virtual void SetVisible(bool visible) = 0;

  ///
  /// Get visibility
  ///
  /*--acf()--*/
  virtual bool GetVisible() = 0;

  ///
  /// Get profile object, maybe null
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfProfile> GetProfile() = 0;

  ///
  /// Returns the number of frames that currently exist.
  ///
  /*--acf()--*/
  virtual size_t GetFrameCount() = 0;

  ///
  /// Returns the identifiers of all existing frames.
  ///
  /*--acf(count_func=identifiers:GetFrameCount)--*/
  virtual void GetFrameIdentifiers(std::vector<int64>& identifiers) = 0;

  ///
  /// Returns the names of all existing frames.
  ///
  /*--acf()--*/
  virtual void GetFrameNames(std::vector<AcfString>& names) = 0;

  ///
  /// Returns the frame with the specified identifier, or NULL if not found.
  ///
  /*--acf(capi_name=get_frame_byident)--*/
  virtual AcfRefPtr<AcfFrame> GetFrame(int64 identifier) = 0;

  ///
  /// Returns the frame with the specified name, or NULL if not found.
  ///
  /*--acf(optional_param=name)--*/
  virtual AcfRefPtr<AcfFrame> GetFrame(const AcfString& name) = 0;
};

///
/// New Window delegate,
/// set a new browser to host target page.
/// Request will be handled while object was destroyed without handled.
///
/*--acf(source=library)--*/
class AcfNewWindowDelegate : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Set a browser to handle the new window
  /// new browser's profile must suit the host browser's profile,
  /// otherwise return false.
  ///
  /*--acf()--*/
  virtual bool SetNewBrowser(AcfRefPtr<AcfBrowser> browser) = 0;

  ///
  /// Get target url
  ///
  /*--acf()--*/
  virtual AcfString GetTargetURL() = 0;

  ///
  /// Put if user has been handled the request.
  /// This method will send the final request to browser.
  ///
  /*--acf()--*/
  virtual void HandleRequest(bool handled) = 0;
};

#endif