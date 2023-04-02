#ifndef ACF_E_UTIL_H_
#define ACF_E_UTIL_H_

#include "acf_types.h"
#include "include/internal/acf_string.h"

#include <windows.h>

LPSTR GetEString(const AcfString& str);

DLL_EXPORTS(ObjectAddRef, void)(void* obj, int type);

DLL_EXPORTS(ObjectRelease, void)(void* obj, int type);

#endif
