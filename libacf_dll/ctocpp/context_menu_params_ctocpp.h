// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=654dada456d425269768425dfc6de4eea5ef4e23$
//

#ifndef ACF_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_
#define ACF_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_
#pragma once

#include "include/acf_context_menu.h"
#include "include/capi/acf_context_menu_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfContextMenuParamsCToCpp
    : public AcfCToCppRefCounted<AcfContextMenuParamsCToCpp,
                                 AcfContextMenuParams,
                                 acf_context_menu_params_t> {
 public:
  AcfContextMenuParamsCToCpp();
  virtual ~AcfContextMenuParamsCToCpp();

  // AcfContextMenuParams methods.
  int GetXCoord() override;
  int GetYCoord() override;
  TypeFlags GetTypeFlags() override;
  AcfString GetLinkUrl() override;
  AcfString GetUnfilteredLinkUrl() override;
  AcfString GetSourceUrl() override;
  AcfString GetPageUrl() override;
  AcfString GetFrameUrl() override;
  AcfString GetFrameCharset() override;
  MediaType GetMediaType() override;
  MediaStateFlags GetMediaStateFlags() override;
  AcfString GetSelectionText() override;
  bool IsEditable() override;
  EditStateFlags GetEditStateFlags() override;
};

#endif  // ACF_CTOCPP_CONTEXT_MENU_PARAMS_CTOCPP_H_