// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=f6a4d48c6253c56fc245197717f6ca35a90f1077$
//

#ifndef ACF_CPPTOC_PROFILE_CPPTOC_H_
#define ACF_CPPTOC_PROFILE_CPPTOC_H_
#pragma once

#include "include/acf_profile.h"
#include "include/capi/acf_profile_capi.h"
#include "libacf_dll/cpptoc/cpptoc_ref_counted.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class AcfProfileCppToC
    : public AcfCppToCRefCounted<AcfProfileCppToC, AcfProfile, acf_profile_t> {
 public:
  AcfProfileCppToC();
  virtual ~AcfProfileCppToC();
};

#endif  // ACF_CPPTOC_PROFILE_CPPTOC_H_
