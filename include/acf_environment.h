#ifndef ACF_ENVIRONMENT_H_
#define ACF_ENVIRONMENT_H_

#include "include/acf_browser.h"
#include "include/acf_profile.h"
#include "include/internal/acf_def.h"
#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_types_wrappers.h"

#include <string>
#include <wtypes.h>

class AcfProfile;
class AcfEnvironment;
class AcfBrowser;
class AcfBrowserHandler;
class AcfProfileHandler;

///
/// Environment event handler
///
/*--acf(source=client)--*/
class AcfEnvironmentHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// called when the environment has been initialized
  ///
  /*--acf()--*/
  virtual void OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) {}

  ///
  /// called before environment destroyed
  ///
  /*--acf()--*/
  virtual void OnEnvironmentDestroyed(AcfRefPtr<AcfEnvironment> env) {}
};

///
/// ACF's environment which host a browser environment.
/// A user data dir can create a environment,
/// Do not create environment on the same user data dir.
///
/*--acf(source=library)--*/
class AcfEnvironment : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Init the acf context, this method must be called before any acf operation.
  /// Method will create a thread to process the ipc message.
  ///
  /*--acf()--*/
  static bool InitACFContext();

  ///
  /// Quit the acf context,
  /// call the method will destroy the connection with the browser.
  ///
  /*--acf()--*/
  static bool QuitACFContext();

  ///
  /// Create new environment on target user data dir
  ///
  /*--acf(optional_param=handler)--*/
  static AcfRefPtr<AcfEnvironment> CreateEnvironment(
      const AcfString& browser_path,
      const AcfEnvironmentSettings& settings,
      AcfRefPtr<AcfEnvironmentHandler> handler);

  ///
  /// Is same object
  ///
  /*--acf()--*/
  virtual bool IsSame(AcfRefPtr<AcfEnvironment> that) = 0;

  ///
  /// Get object remote ready
  ///
  /*--acf()--*/
  virtual bool IsValid() = 0;

  ///
  /// Get Client Handler
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfEnvironmentHandler> GetHandler() = 0;

  ///
  /// Get ACF Components version
  ///
  /*--acf()--*/
  virtual AcfString GetBrowserVersion() = 0;

  ///
  /// Get Browser Process PID
  ///
  /*--acf()--*/
  virtual uint32 GetProcessPID() = 0;

  ///
  /// Quit and wait for browser process
  /// return process exit code
  ///
  /*--acf()--*/
  virtual int Terminate() = 0;

  ///
  /// Create a profile hosted a user profile
  /// each path could only create a profile
  ///
  /*--acf(optional_param=handler)--*/
  virtual AcfRefPtr<AcfProfile> CreateProfile(
      const AcfString& path,
      AcfRefPtr<AcfProfileHandler> handler) = 0;

  ///
  /// Create browser from environment (async)
  /// return object immediately but the object was invalid.
  ///
  /*--acf(optional_param=profile, optional_param=handler)--*/
  virtual AcfRefPtr<AcfBrowser> CreateBrowser(
      AcfRefPtr<AcfProfile> profile,
      AcfRefPtr<AcfBrowserHandler> handler,
      const AcfBrowserCreateParams& params,
      AcfUserData user_data) = 0;
};

#endif