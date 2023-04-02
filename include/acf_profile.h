#ifndef ACF_PROFILE_H_
#define ACF_PROFILE_H_

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_types.h"
#include "include/acf_callback.h"

class AcfProfile;
class AcfProfileHandler;
class AcfCompleteHandler;

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
  /// Remove browsing data when running profile,
  /// when completed it will call OnProfileRemoveDataCompleted
  ///
  /*--acf(optional_param=handler)--*/
  virtual void RemoveBrowsingData(RemoveDataType data_type,
                                  bool no_checks,
                                  AcfRefPtr<AcfCompleteHandler> handler) = 0;
};

#endif