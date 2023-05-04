// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=b836fec069c20d017ce7841e9b42cea729103272$
//

#ifndef ACF_CTOCPP_PROFILE_CTOCPP_H_
#define ACF_CTOCPP_PROFILE_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_environment.h"
#include "include/acf_profile.h"
#include "include/acf_values.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfProfileCToCpp
    : public AcfCToCppRefCounted<AcfProfileCToCpp, AcfProfile, acf_profile_t> {
 public:
  AcfProfileCToCpp();
  virtual ~AcfProfileCToCpp();

  // AcfProfile methods.
  AcfRefPtr<AcfEnvironment> GetEnvironment() override;
  bool IsValid() override;
  AcfString GetPath() override;
  void SetPreference(const AcfString& name,
                     AcfRefPtr<AcfValue> value,
                     AcfRefPtr<AcfCompleteHandler> handler) override;
  void RemoveBrowsingData(RemoveDataType data_type,
                          bool no_checks,
                          AcfRefPtr<AcfCompleteHandler> handler) override;
  AcfRefPtr<AcfCookieManager> GetCookieManager() override;
};

#endif  // ACF_CTOCPP_PROFILE_CTOCPP_H_
