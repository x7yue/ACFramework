// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=cda093ca561dfdafd14e498cd28605a56dbf877c$
//

#include "libacf_dll/cpptoc/profile_cpptoc.h"
#include "libacf_dll/ctocpp/profile_handler_ctocpp.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

acf_profile_handler_t* ACF_CALLBACK
profile_get_handler(struct _acf_profile_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfRefPtr<AcfProfileHandler> _retval =
      AcfProfileCppToC::Get(self)->GetHandler();

  // Return type: refptr_diff
  return AcfProfileHandlerCToCpp::Unwrap(_retval);
}

int ACF_CALLBACK profile_is_valid(struct _acf_profile_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfProfileCppToC::Get(self)->IsValid();

  // Return type: bool
  return _retval;
}

acf_string_userfree_t ACF_CALLBACK
profile_get_path(struct _acf_profile_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfString _retval = AcfProfileCppToC::Get(self)->GetPath();

  // Return type: string
  return _retval.DetachToUserFree();
}

void ACF_CALLBACK profile_remove_browsing_data(struct _acf_profile_t* self,
                                               acf_remove_data_type_t data_type,
                                               int no_checks,
                                               acf_user_data_t token) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;

  // Execute
  AcfProfileCppToC::Get(self)->RemoveBrowsingData(
      data_type, no_checks ? true : false, token);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfProfileCppToC::AcfProfileCppToC() {
  GetStruct()->get_handler = profile_get_handler;
  GetStruct()->is_valid = profile_is_valid;
  GetStruct()->get_path = profile_get_path;
  GetStruct()->remove_browsing_data = profile_remove_browsing_data;
}

// DESTRUCTOR - Do not edit by hand.

AcfProfileCppToC::~AcfProfileCppToC() {}

template <>
AcfRefPtr<AcfProfile>
AcfCppToCRefCounted<AcfProfileCppToC, AcfProfile, acf_profile_t>::UnwrapDerived(
    AcfWrapperType type,
    acf_profile_t* s) {
  return nullptr;
}

template <>
AcfWrapperType AcfCppToCRefCounted<AcfProfileCppToC,
                                   AcfProfile,
                                   acf_profile_t>::kWrapperType = WT_PROFILE;
