// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=b1ed477c0b45e7eb1d809c92d514af327702f39c$
//

#ifndef ACF_CTOCPP_ENVIRONMENT_HANDLER_CTOCPP_H_
#define ACF_CTOCPP_ENVIRONMENT_HANDLER_CTOCPP_H_
#pragma once

#include "include/acf_browser.h"
#include "include/acf_environment.h"
#include "include/acf_profile.h"
#include "include/capi/acf_browser_capi.h"
#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class AcfEnvironmentHandlerCToCpp
    : public AcfCToCppRefCounted<AcfEnvironmentHandlerCToCpp,
                                 AcfEnvironmentHandler,
                                 acf_environment_handler_t> {
 public:
  AcfEnvironmentHandlerCToCpp();
  virtual ~AcfEnvironmentHandlerCToCpp();

  // AcfEnvironmentHandler methods.
  void OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) override;
  void OnEnvironmentDestroyed(AcfRefPtr<AcfEnvironment> env) override;
};

#endif  // ACF_CTOCPP_ENVIRONMENT_HANDLER_CTOCPP_H_
