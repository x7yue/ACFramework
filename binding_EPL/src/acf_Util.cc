#include "acf_Util.h"
#include "include/acf_environment.h"

LPSTR GetEString(const AcfString& str) {
  if (str.empty()) return 0;

  size_t size = str.length() + 1;
  LPSTR pstr = (LPSTR)LocalAlloc(LMEM_ZEROINIT, size);
  memset(pstr, 0, size);

  strcpy(pstr, str.c_str());

  return pstr;
}

DLL_EXPORTS(ObjectAddRef, void)(void* obj, int type) {
  if (!obj) return;

  switch (type) {
    case 0:
      static_cast<AcfEnvironment*>(obj)->AddRef();
      break;
    case 1:
      static_cast<AcfBrowser*>(obj)->AddRef();
      break;
    case 2:
      static_cast<AcfProfile*>(obj)->AddRef();
      break;
    case 3:
      static_cast<AcfNewWindowDelegate*>(obj)->AddRef();
      break;
    default:
      break;
  }
}

DLL_EXPORTS(ObjectRelease, void)(void* obj, int type) {
  if (!obj) return;

  switch (type) {
    case 0:
      static_cast<AcfEnvironment*>(obj)->Release();
      break;
    case 1:
      static_cast<AcfBrowser*>(obj)->Release();
      break;
    case 2:
      static_cast<AcfProfile*>(obj)->Release();
      break;
    case 3:
      static_cast<AcfNewWindowDelegate*>(obj)->Release();
      break;
    default:
      break;
  }
}
