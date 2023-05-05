#ifndef ACF_ENVIRONMENT_H_
#define ACF_ENVIRONMENT_H_

#include "include/acf_browser.h"
#include "include/acf_profile.h"
#include "include/acf_values.h"
#include "include/internal/acf_def.h"
#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_types_wrappers.h"

#include <string>
#include <wtypes.h>

class AcfValue;
class AcfBinaryValue;
class AcfDictionaryValue;
class AcfListValue;
class AcfProfile;
class AcfEnvironment;
class AcfBrowser;
class AcfBrowserHandler;
class AcfCookie;

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
  virtual void OnInitialized(AcfRefPtr<AcfEnvironment> env, bool success) {}
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
  /// Creates a new value object.
  ///
  /*--acf()--*/
  static AcfRefPtr<AcfValue> CreateValue();

  ///
  /// Creates a new object that is not owned by any other object. The specified
  /// |data| will be copied.
  ///
  /*--acf()--*/
  static AcfRefPtr<AcfBinaryValue> CreateBinary(const void* data, size_t data_size);

  ///
  /// Creates a new object that is not owned by any other object.
  ///
  /*--acf()--*/
  static AcfRefPtr<AcfDictionaryValue> CreateDictionary();

  ///
  /// Creates a new object that is not owned by any other object.
  ///
  /*--acf()--*/
  static AcfRefPtr<AcfListValue> CreateList();

  ///
  /// Create a default cookie data.
  ///
  /*--acf()--*/
  static AcfRefPtr<AcfCookie> CreateCookie();

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
  /// Get default profile
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfProfile> GetDefaultProfile() = 0;

  ///
  /// Create a profile hosted a user profile
  /// each path could only create a profile
  ///
  /*--acf(optional_param=handler)--*/
  virtual AcfRefPtr<AcfProfile> CreateProfile(
      const AcfString& path,
      AcfRefPtr<AcfCompleteHandler> handler) = 0;

  ///
  /// Create browser from environment (async)
  /// return object immediately but the object was invalid.
  ///
  /*--acf(optional_param=profile, optional_param=handler, optional_param=extra_info)--*/
  virtual AcfRefPtr<AcfBrowser> CreateBrowser(
      AcfRefPtr<AcfProfile> profile,
      AcfRefPtr<AcfBrowserHandler> handler,
      const AcfBrowserCreateParams& params,
      AcfRefPtr<AcfDictionaryValue> extra_info) = 0;
};

#endif