// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=0a074285ebb7832664d1c3bc7c7cf22e435eac4d$
//

#ifndef ACF_CTOCPP_PROFILE_HANDLER_CTOCPP_H_
#define ACF_CTOCPP_PROFILE_HANDLER_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_profile.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class AcfProfileHandlerCToCpp
    : public AcfCToCppRefCounted<AcfProfileHandlerCToCpp,
                                 AcfProfileHandler,
                                 acf_profile_handler_t> {
 public:
  AcfProfileHandlerCToCpp();
  virtual ~AcfProfileHandlerCToCpp();

  // AcfProfileHandler methods.
  void OnProfileCreated(AcfRefPtr<AcfProfile> profile) override;
  void OnProfileDestroyed(AcfRefPtr<AcfProfile> profile) override;
};

#endif  // ACF_CTOCPP_PROFILE_HANDLER_CTOCPP_H_