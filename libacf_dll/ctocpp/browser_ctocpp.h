// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=9c624c6fd5ea27168e5e3e72fc9d1d7101a9cf0b$
//

#ifndef ACF_CTOCPP_BROWSER_CTOCPP_H_
#define ACF_CTOCPP_BROWSER_CTOCPP_H_
#pragma once

#include <vector>
#include "include/acf_browser.h"
#include "include/acf_environment.h"
#include "include/acf_frame.h"
#include "include/acf_profile.h"
#include "include/acf_values.h"
#include "include/capi/acf_browser_capi.h"
#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_frame_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfBrowserCToCpp
    : public AcfCToCppRefCounted<AcfBrowserCToCpp, AcfBrowser, acf_browser_t> {
 public:
  AcfBrowserCToCpp();
  virtual ~AcfBrowserCToCpp();

  // AcfBrowser methods.
  bool IsSame(AcfRefPtr<AcfBrowser> that) override;
  AcfRefPtr<AcfBrowserHandler> GetHandler() override;
  AcfRefPtr<AcfDictionaryValue> GetExtraInfo() override;
  AcfRefPtr<AcfEnvironment> GetEnvironment() override;
  void Close(bool force) override;
  AcfWindowHandle GetWindowHandle() override;
  bool IsValid() override;
  bool CanGoBack() override;
  bool CanGoForward() override;
  void GoBack() override;
  void GoForward() override;
  void Reload(bool ignore_cache) override;
  void Stop() override;
  bool IsLoading() override;
  void LoadURL(const AcfString& url) override;
  AcfString GetURL() override;
  AcfString GetTitle() override;
  void Focus() override;
  void SetVisible(bool visible) override;
  bool GetVisible() override;
  AcfRefPtr<AcfProfile> GetProfile() override;
  size_t GetFrameCount() override;
  void GetFrameIdentifiers(std::vector<int64>& identifiers) override;
  void GetFrameNames(std::vector<AcfString>& names) override;
  AcfRefPtr<AcfFrame> GetFrame(int64 identifier) override;
  AcfRefPtr<AcfFrame> GetFrame(const AcfString& name) override;
  AcfRefPtr<AcfFrame> GetMainFrame() override;
  void SendKeyEvent(const AcfKeyEvent& event) override;
  void SendMouseClickEvent(const AcfMouseEvent& event,
                           MouseButtonType type,
                           bool mouseUp,
                           int clickCount) override;
  void SendMouseMoveEvent(const AcfMouseEvent& event, bool mouseLeave) override;
  void SendMouseWheelEvent(const AcfMouseEvent& event,
                           int deltaX,
                           int deltaY) override;
  void SetAudioMuted(bool muted) override;
  bool IsAudioMuted() override;
  void ToggleDevtools() override;
  void OpenTaskManager() override;
  void RaiseFindBar() override;
  void ZoomPage(ZoomType zoom_type) override;
};

#endif  // ACF_CTOCPP_BROWSER_CTOCPP_H_
