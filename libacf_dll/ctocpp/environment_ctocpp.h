// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=83e5c2b6844d84a46a6a6b1993f53c13408ce405$
//

#ifndef ACF_CTOCPP_ENVIRONMENT_CTOCPP_H_
#define ACF_CTOCPP_ENVIRONMENT_CTOCPP_H_
#pragma once

#include "include/acf_browser.h"
#include "include/acf_environment.h"
#include "include/acf_profile.h"
#include "include/capi/acf_browser_capi.h"
#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfEnvironmentCToCpp : public AcfCToCppRefCounted<AcfEnvironmentCToCpp,
                                                        AcfEnvironment,
                                                        acf_environment_t> {
 public:
  AcfEnvironmentCToCpp();
  virtual ~AcfEnvironmentCToCpp();

  // AcfEnvironment methods.
  bool IsSame(AcfRefPtr<AcfEnvironment> that) override;
  bool IsValid() override;
  AcfRefPtr<AcfEnvironmentHandler> GetHandler() override;
  AcfString GetBrowserVersion() override;
  uint32 GetProcessPID() override;
  int Terminate() override;
  AcfRefPtr<AcfProfile> CreateProfile(
      const AcfString& path,
      AcfRefPtr<AcfProfileHandler> handler) override;
  AcfRefPtr<AcfBrowser> CreateBrowser(AcfRefPtr<AcfProfile> profile,
                                      AcfRefPtr<AcfBrowserHandler> handler,
                                      const AcfBrowserCreateParams& params,
                                      AcfUserData user_data) override;
};

#endif  // ACF_CTOCPP_ENVIRONMENT_CTOCPP_H_