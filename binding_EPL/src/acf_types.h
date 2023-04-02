#ifndef ACF_E_TYPES_H_
#define ACF_E_TYPES_H_

#define DLL_EXPORTS(name, type) \
  extern "C" __declspec(dllexport) type __cdecl acf_##name

#endif
