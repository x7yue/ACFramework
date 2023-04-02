#include "acf_ebrowser.h"

#include "acf_Util.h"
#include "include/acf_browser.h"

extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];
extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];

namespace {

BOOL ACF_CALLBACK is_same(AcfBrowser* obj, AcfBrowser* that) {
  return obj->IsSame(that);
}

BOOL ACF_CALLBACK is_valid(AcfBrowser* obj) { return obj->IsValid(); }

BOOL ACF_CALLBACK get_env(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfEnvironment> env = obj->GetEnvironment();

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_environment;
  }

  return !!env.get();
}

BOOL ACF_CALLBACK get_profile(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfProfile> env = obj->GetProfile();

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_profile;
  }

  return !!env.get();
}

HWND ACF_CALLBACK get_hwnd(AcfBrowser* obj) { return obj->GetWindowHandle(); }

void ACF_CALLBACK close(AcfBrowser* obj, bool force) { obj->Close(force); }

BOOL ACF_CALLBACK can_goback(AcfBrowser* obj) { return obj->CanGoBack(); }

BOOL ACF_CALLBACK can_goforward(AcfBrowser* obj) { return obj->CanGoForward(); }

void ACF_CALLBACK goback(AcfBrowser* obj) { obj->GoBack(); }

void ACF_CALLBACK goforward(AcfBrowser* obj) { obj->GoForward(); }

void ACF_CALLBACK reload(AcfBrowser* obj, bool cache) { obj->Reload(cache); }

void ACF_CALLBACK stop(AcfBrowser* obj) { obj->Stop(); }

BOOL ACF_CALLBACK isloading(AcfBrowser* obj) { return obj->IsLoading(); }

void ACF_CALLBACK load_url(AcfBrowser* obj, LPCSTR url) {
  return obj->LoadURL(url);
}

LPSTR ACF_CALLBACK get_url(AcfBrowser* obj) {
  return GetEString(obj->GetURL());
}

LPSTR ACF_CALLBACK get_title(AcfBrowser* obj) {
  return GetEString(obj->GetTitle());
}

void ACF_CALLBACK focus(AcfBrowser* obj) { obj->Focus(); }

void ACF_CALLBACK set_visible(AcfBrowser* obj, bool visible) {
  obj->SetVisible(visible);
}

BOOL ACF_CALLBACK get_visible(AcfBrowser* obj) { return obj->GetVisible(); }

void* ACF_CALLBACK get_user_data(AcfBrowser* obj) { return obj->GetUserData(); }

/// <summary>
/// New Window Delagate
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>

BOOL ACF_CALLBACK set_new_browser(AcfNewWindowDelegate* obj,
                                  AcfBrowser* browser) {
  return obj->SetNewBrowser(browser);
}

LPSTR ACF_CALLBACK get_target_url(AcfNewWindowDelegate* obj) {
  return GetEString(obj->GetTargetURL());
}

void ACF_CALLBACK handle_new_window(AcfNewWindowDelegate* obj, bool handle) {
  obj->HandleRequest(handle);
}

}  // namespace

DWORD acf_cpp_fntable_browser[] = {
    (DWORD)is_same,     (DWORD)is_valid,      (DWORD)get_env,
    (DWORD)get_profile, (DWORD)get_hwnd,      (DWORD)close,
    (DWORD)can_goback,  (DWORD)can_goforward, (DWORD)goback,
    (DWORD)goforward,   (DWORD)reload,        (DWORD)stop,
    (DWORD)isloading,   (DWORD)load_url,      (DWORD)get_url,
    (DWORD)get_title,   (DWORD)focus,         (DWORD)set_visible,
    (DWORD)get_visible, (DWORD)get_user_data,
};

DWORD acf_cpp_fntable_new_window_delegate[] = {
    (DWORD)set_new_browser,
    (DWORD)get_target_url,
    (DWORD)handle_new_window,
};
