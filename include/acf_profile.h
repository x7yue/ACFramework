#ifndef ACF_PROFILE_H_
#define ACF_PROFILE_H_

#include "include/acf_callback.h"
#include "include/acf_values.h"
#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_types.h"
#include "include/internal/acf_types_wrappers.h"

#include <vector>

class AcfCookie;
class AcfValue;
class AcfProfile;
class AcfProfileHandler;
class AcfCompleteHandler;
class AcfCookieManager;
class AcfCookieVisitor;
class AcfCookiesGetter;
class AcfEnvironment;

///
/// Profile handler
///
/*--acf(source=client)--*/
class AcfProfileHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called on profile created on remote,
  /// maybe created with failed.
  ///
  /*--acf()--*/
  virtual void OnProfileCreated(AcfRefPtr<AcfProfile> profile) {}

  ///
  /// Called when profile destroyed
  ///
  /*--acf()--*/
  virtual void OnProfileDestroyed(AcfRefPtr<AcfProfile> profile) {}
};

///
/// ACF's profile object for create browser in environment.
/// In chromium, it is user profile
///
/*--acf(source=library)--*/
class AcfProfile : public virtual AcfBaseRefCounted {
 public:
  typedef acf_remove_data_type_t RemoveDataType;

  ///
  /// Get event handler
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfProfileHandler> GetHandler() = 0;

  ///
  /// Get host environment object
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfEnvironment> GetEnvironment() = 0;

  ///
  /// Get object remote state
  ///
  /*--acf()--*/
  virtual bool IsValid() = 0;

  ///
  /// Get profile storage path
  ///
  /*--acf()--*/
  virtual AcfString GetPath() = 0;

  ///
  /// Set the |value| associated with preference |name|.
  ///
  /*--acf(optional_param=value, optional_param=handler)--*/
  virtual void SetPreference(const AcfString& name,
                             AcfRefPtr<AcfValue> value,
                             AcfRefPtr<AcfCompleteHandler> handler) = 0;
  
  ///
  /// Remove browsing data when running profile,
  /// when completed it will call OnProfileRemoveDataCompleted
  ///
  /*--acf(optional_param=handler)--*/
  virtual void RemoveBrowsingData(RemoveDataType data_type,
                                  bool no_checks,
                                  AcfRefPtr<AcfCompleteHandler> handler) = 0;
  
  ///
  /// Get cookie manager for current profile
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfCookieManager> GetCookieManager() = 0;

  ///
  /// Create a default cookie data.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfCookie> CreateCookie(const AcfString& name,
                                            const AcfString& value,
                                            const AcfString& domain,
                                            const AcfString& path) = 0;
};

///
/// Cookie data storage
///
/*--acf(source=library)--*/
class AcfCookie : public virtual AcfBaseRefCounted {
 public:
  typedef acf_cookie_same_site_t AcfCookieSameSite;
  typedef acf_cookie_priority_t AcfCookiePriority;

  ///
  /// Get cookie name
  ///
  /*--acf()--*/
  virtual AcfString GetName() = 0;

  ///
  /// Set cookie name
  ///
  /*--acf()--*/
  virtual void SetName(const AcfString& value) = 0;

  ///
  /// Get cookie value
  ///
  /*--acf()--*/
  virtual AcfString GetValue() = 0;

  ///
  /// Set cookie value
  ///
  /*--acf()--*/
  virtual void SetValue(const AcfString& value) = 0;

  ///
  /// Get cookie domain
  ///
  /*--acf()--*/
  virtual AcfString GetDomain() = 0;

  ///
  /// Set cookie domain
  ///
  /*--acf()--*/
  virtual void SetDomain(const AcfString& value) = 0;

  ///
  /// Get cookie path
  ///
  /*--acf()--*/
  virtual AcfString GetPath() = 0;

  ///
  /// Set cookie path
  ///
  /*--acf()--*/
  virtual void SetPath(const AcfString& value) = 0;

  ///
  /// Is cookie httponly
  ///
  /*--acf()--*/
  virtual bool IsHttponly() = 0;

  ///
  /// Set cookie httponly
  ///
  /*--acf()--*/
  virtual void SetHttponly(bool value) = 0;

  ///
  /// Is cookie secure
  ///
  /*--acf()--*/
  virtual bool IsSecure() = 0;

  ///
  /// Set cookie secure
  ///
  /*--acf()--*/
  virtual void SetSecure(bool value) = 0;

  ///
  /// Get same site infomation
  ///
  /*--acf(default_retval=ACF_COOKIE_SAME_SITE_NO_RESTRICTION)--*/
  virtual AcfCookieSameSite GetSameSite() = 0;

  ///
  /// Set same site infomation
  ///
  /*--acf()--*/
  virtual void SetSameSite(AcfCookieSameSite value) = 0;

  ///
  /// Get priority
  ///
  /*--acf(default_retval=ACF_COOKIE_PRIORITY_MEDIUM)--*/
  virtual AcfCookiePriority GetPriority() = 0;

  ///
  /// Set priority
  ///
  /*--acf()--*/
  virtual void SetPriority(AcfCookiePriority value) = 0;

  ///
  /// Get create time
  ///
  /*--acf()--*/
  virtual double GetCreation() = 0;

  ///
  /// Set create time
  ///
  /*--acf()--*/
  virtual void SetCreation(double value) = 0;

  ///
  /// Get expiry time
  ///
  /*--acf()--*/
  virtual double GetExpiry() = 0;

  ///
  /// Set expiry time
  ///
  /*--acf()--*/
  virtual void SetExpiry(double value) = 0;

  ///
  /// Get last access time
  ///
  /*--acf()--*/
  virtual double GetLastAccess() = 0;

  ///
  /// Set last access time
  ///
  /*--acf()--*/
  virtual void SetLastAccess(double value) = 0;

  ///
  /// Get last update time
  ///
  /*--acf()--*/
  virtual double GetLastUpdate() = 0;

  ///
  /// Set last update time
  ///
  /*--acf()--*/
  virtual void SetLastUpdate(double value) = 0;
};

///
/// Cookie getter
///
/*--acf(source=library)--*/
class AcfCookiesGetter : public virtual AcfBaseRefCounted {
 public:
  typedef std::vector<AcfRefPtr<AcfCookie>> CookiesGetter;

  ///
  /// Get count
  ///
  /*--acf()--*/
  virtual size_t GetCookiesCount() = 0;

  ///
  /// Get cookie data
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfCookie> GetCookieAt(size_t index) = 0;
};

///
/// Cookie visitor
///
/*--acf(source=client)--*/
class AcfCookieVisitor : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called when completed.
  ///
  /*--acf()--*/
  virtual void Visit(AcfRefPtr<AcfCookiesGetter> cookie_getter) = 0;
};

///
/// Class used for managing cookies. The methods of this class may be called on
/// any thread unless otherwise indicated.
///
/*--acf(source=library)--*/
class AcfCookieManager : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Visit cookies on the current thread. The returned cookies are ordered by
  /// longest path, then by earliest creation date. Returns false if cookies
  /// cannot be accessed.
  ///
  /*--acf(optional_param=url)--*/
  virtual void GetCookies(const AcfString& url,
                          bool includeHttpOnly,
                          AcfRefPtr<AcfCookieVisitor> visitor) = 0;

  ///
  /// Sets a cookie given a valid URL and explicit user-provided cookie
  /// attributes. This function expects each attribute to be well-formed. It
  /// will check for disallowed characters (e.g. the ';' character is disallowed
  /// within the cookie value attribute) and fail without setting the cookie if
  /// such characters are found. If |callback| is non-NULL it will be executed
  /// asnychronously on the UI thread after the cookie has been set. Returns
  /// false if an invalid URL is specified or if cookies cannot be accessed.
  ///
  /*--acf(optional_param=callback)--*/
  virtual void SetCookie(const AcfString& url,
                         AcfRefPtr<AcfCookie> cookie,
                         AcfRefPtr<AcfCompleteHandler> callback) = 0;

  ///
  /// Delete all cookies that match the specified parameters. If both |url| and
  /// |cookie_name| values are specified all host and domain cookies matching
  /// both will be deleted. If only |url| is specified all host cookies (but not
  /// domain cookies) irrespective of path will be deleted. If |url| is empty
  /// all cookies for all hosts and domains will be deleted. If |callback| is
  /// non-NULL it will be executed asnychronously on the UI thread after the
  /// cookies have been deleted. Returns false if a non-empty invalid URL is
  /// specified or if cookies cannot be accessed. Cookies can alternately be
  /// deleted using the Visit*Cookies() methods.
  ///
  /*--acf(optional_param=url,optional_param=cookie_name,
          optional_param=callback)--*/
  virtual void DeleteCookies(const AcfString& url,
                             const AcfString& cookie_name,
                             AcfRefPtr<AcfNumberCompleteHandler> callback) = 0;

  ///
  /// Flush the backing store (if any) to disk. If |callback| is non-NULL it
  /// will be executed asnychronously on the UI thread after the flush is
  /// complete. Returns false if cookies cannot be accessed.
  ///
  /*--acf(optional_param=callback)--*/
  virtual void FlushStore(AcfRefPtr<AcfCompleteHandler> callback) = 0;
};

#endif