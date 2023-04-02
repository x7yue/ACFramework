#include "acf_env.h"

#include <windows.h>
#include <iostream>

#include "acf_Util.h"
#include "acf_handler.h"

extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];

DLL_EXPORTS(InitACFContext, BOOL)
() { return AcfEnvironment::InitACFContext(); }

DLL_EXPORTS(QuitACFContext, BOOL)
() { return AcfEnvironment::QuitACFContext(); }

using EnvironmentParams = struct {
  LPCSTR command_line;
  LPCSTR user_data_dir;
};
DLL_EXPORTS(CreateEnvironment, BOOL)
(LPCSTR browser_path, EnvironmentParams* params, LPVOID handler,
 DWORD* retObj) {
  AcfRefPtr<wrapper::EnvironmentHandler> lpHandler(
      new wrapper::EnvironmentHandler(handler));
  AcfEnvironmentSettings settings;

  if (params) {
    AcfString(&settings.command_line).FromString(params->command_line);
    AcfString(&settings.user_data_dir).FromString(params->user_data_dir);
  }

  AcfRefPtr<AcfEnvironment> env =
      AcfEnvironment::CreateEnvironment(browser_path, settings, lpHandler);

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_environment;
  }

  return !!env.get();
}

DLL_EXPORTS(RunMessageLoop, void)() {
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

namespace {

BOOL ACF_CALLBACK is_same(AcfEnvironment* obj, AcfEnvironment* that) {
  return obj->IsSame(that);
}

DWORD ACF_CALLBACK get_handler(AcfEnvironment* obj) {
  return (DWORD)obj->GetHandler().get();
}

LPSTR ACF_CALLBACK get_version(AcfEnvironment* obj) {
  return GetEString(obj->GetBrowserVersion());
}

uint32_t ACF_CALLBACK get_process_id(AcfEnvironment* obj) {
  return obj->GetProcessPID();
}

BOOL ACF_CALLBACK create_profile(AcfEnvironment* obj, LPCSTR path, LPVOID callback, DWORD* retObj) {
  AcfRefPtr<wrapper::ProfileHandler> lphandler(new wrapper::ProfileHandler(callback));
  
  AcfRefPtr<AcfProfile> pf = obj->CreateProfile(path, lphandler);
  
  if (pf) {
    pf->AddRef();
    retObj[1] = (DWORD)pf.get();
    retObj[2] = (DWORD)acf_cpp_fntable_profile;
  }

  return !!pf.get();
}

using BrowserParams = struct {
  HWND parent;
  bool visible;
  int x;
  int y;
  int width;
  int height;
};
BOOL ACF_CALLBACK create_browser(AcfEnvironment* obj, AcfProfile* profile,
                                 BrowserParams* pparams, int udata,
                                 LPVOID callback, DWORD* retObj) {
  AcfRefPtr<wrapper::BrowserHandler> lphandler(
      new wrapper::BrowserHandler(callback));

  AcfBrowserCreateParams params;
  if (pparams) {
    params.parent = pparams->parent;
    params.visible = pparams->visible;
    params.x = pparams->x;
    params.y = pparams->y;
    params.width = pparams->width;
    params.height = pparams->height;
  }

  AcfRefPtr<AcfBrowser> pf = obj->CreateBrowser(profile, lphandler, params, (void*)udata);

  if (pf) {
    pf->AddRef();
    retObj[1] = (DWORD)pf.get();
    retObj[2] = (DWORD)acf_cpp_fntable_browser;
  }

  return !!pf.get();
}

BOOL ACF_CALLBACK is_valid(AcfEnvironment* obj) {
  return obj->IsValid();
}

int ACF_CALLBACK terminate_process(AcfEnvironment* obj) {
  return obj->Terminate();
}

}  // namespacek

DWORD acf_cpp_fntable_environment[] = {
    (DWORD)is_same,        (DWORD)get_handler,       (DWORD)get_version,
    (DWORD)get_process_id, (DWORD)create_profile,    (DWORD)create_browser,
    (DWORD)is_valid,       (DWORD)terminate_process,
};