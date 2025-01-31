// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=e6424f9e3cdeb1103e57ead535b23da77011276b$
//

#include "libacf_dll/cpptoc/environment_cpptoc.h"
#include "libacf_dll/cpptoc/binary_value_cpptoc.h"
#include "libacf_dll/cpptoc/browser_cpptoc.h"
#include "libacf_dll/cpptoc/cookie_cpptoc.h"
#include "libacf_dll/cpptoc/dictionary_value_cpptoc.h"
#include "libacf_dll/cpptoc/list_value_cpptoc.h"
#include "libacf_dll/cpptoc/profile_cpptoc.h"
#include "libacf_dll/cpptoc/value_cpptoc.h"
#include "libacf_dll/ctocpp/browser_handler_ctocpp.h"
#include "libacf_dll/ctocpp/complete_handler_ctocpp.h"
#include "libacf_dll/ctocpp/environment_handler_ctocpp.h"
#include "libacf_dll/template_util.h"

// GLOBAL FUNCTIONS - Body may be edited by hand.

ACF_EXPORT int acf_environment_init_acfcontext() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  bool _retval = AcfEnvironment::InitACFContext();

  // Return type: bool
  return _retval;
}

ACF_EXPORT int acf_environment_quit_acfcontext() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  bool _retval = AcfEnvironment::QuitACFContext();

  // Return type: bool
  return _retval;
}

ACF_EXPORT acf_environment_t* acf_environment_create(
    const acf_string_t* browser_path,
    const struct _acf_environment_settings_t* settings,
    acf_environment_handler_t* handler) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser_path; type: string_byref_const
  if (!browser_path)
    return NULL;
  // Verify param: settings; type: struct_byref_const
  if (!settings)
    return NULL;
  if (!template_util::has_valid_size(settings)) {
    return NULL;
  }
  // Unverified params: handler

  // Translate param: settings; type: struct_byref_const
  AcfEnvironmentSettings settingsObj;
  if (settings)
    settingsObj.Set(*settings, false);

  // Execute
  AcfRefPtr<AcfEnvironment> _retval = AcfEnvironment::CreateEnvironment(
      AcfString(browser_path), settingsObj,
      AcfEnvironmentHandlerCToCpp::Wrap(handler));

  // Return type: refptr_same
  return AcfEnvironmentCppToC::Wrap(_retval);
}

ACF_EXPORT struct _acf_value_t* acf_environment_create_value() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  AcfRefPtr<AcfValue> _retval = AcfEnvironment::CreateValue();

  // Return type: refptr_same
  return AcfValueCppToC::Wrap(_retval);
}

ACF_EXPORT struct _acf_binary_value_t* acf_environment_create_binary(
    const void* data,
    size_t data_size) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: data; type: simple_byaddr
  if (!data)
    return NULL;

  // Execute
  AcfRefPtr<AcfBinaryValue> _retval =
      AcfEnvironment::CreateBinary(data, data_size);

  // Return type: refptr_same
  return AcfBinaryValueCppToC::Wrap(_retval);
}

ACF_EXPORT struct _acf_dictionary_value_t* acf_environment_create_dictionary() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  AcfRefPtr<AcfDictionaryValue> _retval = AcfEnvironment::CreateDictionary();

  // Return type: refptr_same
  return AcfDictionaryValueCppToC::Wrap(_retval);
}

ACF_EXPORT struct _acf_list_value_t* acf_environment_create_list() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  AcfRefPtr<AcfListValue> _retval = AcfEnvironment::CreateList();

  // Return type: refptr_same
  return AcfListValueCppToC::Wrap(_retval);
}

ACF_EXPORT struct _acf_cookie_t* acf_environment_create_cookie() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  AcfRefPtr<AcfCookie> _retval = AcfEnvironment::CreateCookie();

  // Return type: refptr_same
  return AcfCookieCppToC::Wrap(_retval);
}

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int ACF_CALLBACK environment_is_same(struct _acf_environment_t* self,
                                     struct _acf_environment_t* that) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;
  // Verify param: that; type: refptr_same
  if (!that)
    return 0;

  // Execute
  bool _retval = AcfEnvironmentCppToC::Get(self)->IsSame(
      AcfEnvironmentCppToC::Unwrap(that));

  // Return type: bool
  return _retval;
}

int ACF_CALLBACK environment_is_valid(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfEnvironmentCppToC::Get(self)->IsValid();

  // Return type: bool
  return _retval;
}

acf_environment_handler_t* ACF_CALLBACK
environment_get_handler(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfRefPtr<AcfEnvironmentHandler> _retval =
      AcfEnvironmentCppToC::Get(self)->GetHandler();

  // Return type: refptr_diff
  return AcfEnvironmentHandlerCToCpp::Unwrap(_retval);
}

acf_string_userfree_t ACF_CALLBACK
environment_get_browser_version(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfString _retval = AcfEnvironmentCppToC::Get(self)->GetBrowserVersion();

  // Return type: string
  return _retval.DetachToUserFree();
}

uint32 ACF_CALLBACK
environment_get_process_pid(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  uint32 _retval = AcfEnvironmentCppToC::Get(self)->GetProcessPID();

  // Return type: simple
  return _retval;
}

int ACF_CALLBACK environment_terminate(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  int _retval = AcfEnvironmentCppToC::Get(self)->Terminate();

  // Return type: simple
  return _retval;
}

struct _acf_profile_t* ACF_CALLBACK
environment_get_default_profile(struct _acf_environment_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfRefPtr<AcfProfile> _retval =
      AcfEnvironmentCppToC::Get(self)->GetDefaultProfile();

  // Return type: refptr_same
  return AcfProfileCppToC::Wrap(_retval);
}

struct _acf_profile_t* ACF_CALLBACK
environment_create_profile(struct _acf_environment_t* self,
                           const acf_string_t* path,
                           acf_complete_handler_t* handler) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;
  // Verify param: path; type: string_byref_const
  if (!path)
    return NULL;
  // Unverified params: handler

  // Execute
  AcfRefPtr<AcfProfile> _retval =
      AcfEnvironmentCppToC::Get(self)->CreateProfile(
          AcfString(path), AcfCompleteHandlerCToCpp::Wrap(handler));

  // Return type: refptr_same
  return AcfProfileCppToC::Wrap(_retval);
}

acf_browser_t* ACF_CALLBACK
environment_create_browser(struct _acf_environment_t* self,
                           struct _acf_profile_t* profile,
                           acf_browser_handler_t* handler,
                           const struct _acf_browser_create_params_t* params,
                           struct _acf_dictionary_value_t* extra_info) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;
  // Verify param: params; type: struct_byref_const
  if (!params)
    return NULL;
  if (!template_util::has_valid_size(params)) {
    return NULL;
  }
  // Unverified params: profile, handler, extra_info

  // Translate param: params; type: struct_byref_const
  AcfBrowserCreateParams paramsObj;
  if (params)
    paramsObj.Set(*params, false);

  // Execute
  AcfRefPtr<AcfBrowser> _retval =
      AcfEnvironmentCppToC::Get(self)->CreateBrowser(
          AcfProfileCppToC::Unwrap(profile),
          AcfBrowserHandlerCToCpp::Wrap(handler), paramsObj,
          AcfDictionaryValueCppToC::Unwrap(extra_info));

  // Return type: refptr_same
  return AcfBrowserCppToC::Wrap(_retval);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfEnvironmentCppToC::AcfEnvironmentCppToC() {
  GetStruct()->is_same = environment_is_same;
  GetStruct()->is_valid = environment_is_valid;
  GetStruct()->get_handler = environment_get_handler;
  GetStruct()->get_browser_version = environment_get_browser_version;
  GetStruct()->get_process_pid = environment_get_process_pid;
  GetStruct()->terminate = environment_terminate;
  GetStruct()->get_default_profile = environment_get_default_profile;
  GetStruct()->create_profile = environment_create_profile;
  GetStruct()->create_browser = environment_create_browser;
}

// DESTRUCTOR - Do not edit by hand.

AcfEnvironmentCppToC::~AcfEnvironmentCppToC() {}

template <>
AcfRefPtr<AcfEnvironment>
AcfCppToCRefCounted<AcfEnvironmentCppToC, AcfEnvironment, acf_environment_t>::
    UnwrapDerived(AcfWrapperType type, acf_environment_t* s) {
  return nullptr;
}

template <>
AcfWrapperType AcfCppToCRefCounted<AcfEnvironmentCppToC,
                                   AcfEnvironment,
                                   acf_environment_t>::kWrapperType =
    WT_ENVIRONMENT;
