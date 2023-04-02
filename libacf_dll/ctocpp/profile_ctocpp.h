// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=7247c37fc683b8af0c1ec6248568204379dc10a9$
//

#ifndef ACF_CTOCPP_PROFILE_CTOCPP_H_
#define ACF_CTOCPP_PROFILE_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_profile.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfProfileCToCpp
    : public AcfCToCppRefCounted<AcfProfileCToCpp, AcfProfile, acf_profile_t> {
 public:
  AcfProfileCToCpp();
  virtual ~AcfProfileCToCpp();

  // AcfProfile methods.
  AcfRefPtr<AcfProfileHandler> GetHandler() override;
  bool IsValid() override;
  AcfString GetPath() override;
  void RemoveBrowsingData(RemoveDataType data_type,
                          bool no_checks,
                          AcfRefPtr<AcfCompleteHandler> handler) override;
};

#endif  // ACF_CTOCPP_PROFILE_CTOCPP_H_