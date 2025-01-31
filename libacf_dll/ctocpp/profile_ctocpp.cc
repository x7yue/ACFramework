// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=c929db7ef49207fcaf1974771d257656a10d1edd$
//

#include "libacf_dll/ctocpp/profile_ctocpp.h"
#include "libacf_dll/cpptoc/complete_handler_cpptoc.h"
#include "libacf_dll/ctocpp/cookie_manager_ctocpp.h"
#include "libacf_dll/ctocpp/environment_ctocpp.h"
#include "libacf_dll/ctocpp/value_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

AcfRefPtr<AcfEnvironment> AcfProfileCToCpp::GetEnvironment() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_environment))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_environment_t* _retval = _struct->get_environment(_struct);

  // Return type: refptr_same
  return AcfEnvironmentCToCpp::Wrap(_retval);
}

bool AcfProfileCToCpp::IsValid() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, is_valid))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_valid(_struct);

  // Return type: bool
  return _retval ? true : false;
}

AcfString AcfProfileCToCpp::GetPath() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_path))
    return AcfString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_string_userfree_t _retval = _struct->get_path(_struct);

  // Return type: string
  AcfString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void AcfProfileCToCpp::SetPreference(const AcfString& name,
                                     AcfRefPtr<AcfValue> value,
                                     AcfRefPtr<AcfCompleteHandler> handler) {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, set_preference))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  if (name.empty())
    return;
  // Unverified params: value, handler

  // Execute
  _struct->set_preference(_struct, name.GetStruct(),
                          AcfValueCToCpp::Unwrap(value),
                          AcfCompleteHandlerCppToC::Wrap(handler));
}

void AcfProfileCToCpp::RemoveBrowsingData(
    RemoveDataType data_type,
    bool no_checks,
    AcfRefPtr<AcfCompleteHandler> handler) {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, remove_browsing_data))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: handler

  // Execute
  _struct->remove_browsing_data(_struct, data_type, no_checks,
                                AcfCompleteHandlerCppToC::Wrap(handler));
}

AcfRefPtr<AcfCookieManager> AcfProfileCToCpp::GetCookieManager() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_cookie_manager))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_cookie_manager_t* _retval = _struct->get_cookie_manager(_struct);

  // Return type: refptr_same
  return AcfCookieManagerCToCpp::Wrap(_retval);
}

// CONSTRUCTOR - Do not edit by hand.

AcfProfileCToCpp::AcfProfileCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfProfileCToCpp::~AcfProfileCToCpp() {}

template <>
acf_profile_t*
AcfCToCppRefCounted<AcfProfileCToCpp, AcfProfile, acf_profile_t>::UnwrapDerived(
    AcfWrapperType type,
    AcfProfile* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfProfileCToCpp,
                                   AcfProfile,
                                   acf_profile_t>::kWrapperType = WT_PROFILE;
